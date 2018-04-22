/*
  ==============================================================================

    Gridlines.cpp
    Created: 21 Apr 2018 3:55:02pm
    Author:  Luke M Craig

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Gridlines.h"

//==============================================================================
Gridlines::Gridlines()
{
	zoomRatio_ = 2.5f;
	panAngle_ = 0;
	radiusTransform_ = AffineTransform::scale(2);
	polarLineTransform_ = AffineTransform::rotation(float_Pi/12.0f);
	g1s_ = 1;
	g2s_ = 1;
	clickedOn_ = nothingId;
}

Gridlines::~Gridlines()
{
}

void Gridlines::mouseDown(const MouseEvent& e) 
{
	auto point = e.getPosition();
	Point<float> pointf = Point<float>(point.x, point.y);
	pointf.applyTransform(uvTransform_.inverted());
	auto clickAngle = atan2f(pointf.y, pointf.x);

	auto distanceToPhi = abs(clickAngle - panAngle_);
	auto distanceToTheta = abs(clickAngle - speakerAngle_);
	auto distanceToNegativeTheta = abs(clickAngle - -speakerAngle_);
	if (distanceToPhi < CLICK_EPSILON && distanceToPhi<=distanceToTheta && distanceToPhi<=distanceToNegativeTheta) {
		clickedOn_ = phiVectorId;
	}
	else if (distanceToTheta < CLICK_EPSILON && distanceToTheta<=distanceToPhi  && distanceToTheta<=distanceToNegativeTheta) {
		clickedOn_ = positiveThetaVectorId;
	}
	else if (distanceToNegativeTheta < CLICK_EPSILON && distanceToNegativeTheta<=distanceToPhi && distanceToNegativeTheta<=distanceToTheta) {
		clickedOn_ = negativeThetaVectorId;
	}
}

void Gridlines::mouseUp(const MouseEvent& e)
{	
		clickedOn_ = nothingId;
}

void Gridlines::mouseDrag(const MouseEvent& e) 
{
	if (clickedOn_ == nothingId)
		return;
	// TODO clean this up
	auto point = e.getPosition();
	Point<float> pointf = Point<float>(point.x, point.y);
	pointf.applyTransform(uvTransform_.inverted());
	auto clickAngle = atan2f(pointf.y, pointf.x);
	if (clickedOn_ == phiVectorId) {
		panAngle_ = clickAngle;
		// clamp the angle
		panAngle_ = juce::jmax(panAngle_, float_Pi*-0.5f);				// > -90 degrees
		panAngle_ = juce::jmin(panAngle_, float_Pi*0.5f);				// < 90 degrees

		panAngle_ = juce::jmax(panAngle_, -speakerAngle_);				// > -theta
		panAngle_ = juce::jmin(panAngle_, speakerAngle_);				// < theta
	}
	else if (clickedOn_ == positiveThetaVectorId || clickedOn_ == negativeThetaVectorId) {
		if (clickedOn_ == positiveThetaVectorId) {
			speakerAngle_ = clickAngle;
		}
		else if (clickedOn_ == negativeThetaVectorId) {
			speakerAngle_ = -clickAngle;
		}
		// clamp the angle
		speakerAngle_ = juce::jmax(speakerAngle_, MIN_SPEAKERANGLE);	// The speakers can't be in the same position
		speakerAngle_ = juce::jmin(speakerAngle_, float_Pi*0.5f);		// < 90 degrees
		speakerAngle_ = juce::jmax(speakerAngle_, panAngle_);			// > phi
		speakerAngle_ = juce::jmax(speakerAngle_, -panAngle_);			// > -phi
	}
	repaint();
}

void Gridlines::mouseWheelMove(const MouseEvent & e, const MouseWheelDetails & wheel)
{
	zoomRatio_ -= wheel.deltaY;
	zoomRatio_ = juce::jmax(0.1f, zoomRatio_);
	repaint();
}

void Gridlines::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background	   
    g.setColour (Colours::white);
	auto cb = g.getClipBounds();
	float zoomFactor = 1.0f / zoomRatio_;

	// transform into uv coords
	uvTransform_ = AffineTransform();
	// [0.0,height]-> [0.0,1.0], make positive y-axis point up
	// TODO don't do this negative scale
	uvTransform_ = uvTransform_.scaled(cb.getHeight() * zoomFactor, cb.getHeight() * -zoomFactor);
	// rotate so x is pointing up
	uvTransform_ = uvTransform_.rotated(float_Pi * -0.5f);
	// center the origin
	uvTransform_ = uvTransform_.translated(cb.getHeight() * 0.5f, cb.getHeight() * 0.5f); 
	g.addTransform(uvTransform_);
	
	//TODO make these options bools for the component
	//DrawGridlines(g, zoomRatio_);

	g.setColour(Colours::wheat);
	auto arc = Path();
	arc.addCentredArc(0, 0, 1, 1, 0, 0, float_Pi, true);
	g.strokePath(arc, PathStrokeType(0.05f, PathStrokeType::beveled, PathStrokeType::butt));
	
	//g.fillEllipse(dragPoint_.x-0.05f, dragPoint_.y-0.05f, 0.1f, 0.1f);
	DrawVectors(g);

	g.setColour(Colours::white);
	DrawPolarGrid(g);

	g.addTransform(uvTransform_.inverted());
	g.setColour(Colours::black);
	g.drawRect(getLocalBounds(), 3);   // draw an outline around the component
}

void Gridlines::DrawVectors(juce::Graphics & g)
{
	g.setColour(Colours::palegreen);
	g.drawArrow(Line<float>(0, 0, g1s_ * cos(speakerAngle_), g1s_ * sin(speakerAngle_)), .02, ARROW_WIDTH, ARROW_LENGTH);
	g.setColour(Colours::powderblue);
	g.drawArrow(Line<float>(0, 0, g2s_ * cos(speakerAngle_), g2s_ * -sin(speakerAngle_)), .02, ARROW_WIDTH, ARROW_LENGTH);
	
	g.setColour(Colours::orange);
	g.drawArrow(Line<float>(0, 0, cos(panAngle_), sin(panAngle_)), .02, ARROW_WIDTH, ARROW_LENGTH);
}

void Gridlines::DrawPolarGrid(juce::Graphics & g)
{
	DrawPolarGridCircles(g, 4);	
	DrawPolarGridLines(g, 6, 0, polarLineTransform_, 15);	
	DrawPolarGridLines(g, 6, 0, polarLineTransform_.inverted(), -15);
}

void Gridlines::DrawPolarGridLines(juce::Graphics & g, int count, int currentRotation, AffineTransform rotationTransform, int rotationAmount)
{
	if (count < 0)  // base case
		return;
	auto polarLine = Line<float>(0, 0, 10, 0);
	g.drawLine(polarLine, 0.002f);

	DrawPolarDegreeText(g, rotationAmount, currentRotation);

	g.addTransform(rotationTransform); // push each transform on the stack
	DrawPolarGridLines(g, count-1, currentRotation+ rotationAmount, rotationTransform, rotationAmount);
	g.addTransform(rotationTransform.inverted()); // pop each transform off the stack
}

void Gridlines::DrawPolarDegreeText(juce::Graphics & g, int rotationAmount, int currentRotation)
{
	g.setFont(.05f);
	g.addTransform(AffineTransform::scale(1, -1));
	auto textRotation = AffineTransform::rotation(float_Pi, 1.25f, 0);
	if (rotationAmount>0)
		g.addTransform(textRotation);
	auto textRect = Rectangle<float>(1.2f, -0.05f, 1, .1f);
	//g.drawRect(textRect, .01f);	
	if (rotationAmount>0 || currentRotation != 0)
		g.drawText(String(currentRotation) + String(CharPointer_UTF8("\xc2\xb0")), textRect, Justification::bottomLeft);
	if (rotationAmount>0)
		g.addTransform(textRotation.inverted());
	g.addTransform(AffineTransform::scale(1, -1));
}

void Gridlines::DrawPolarGridCircles(juce::Graphics & g, int count)
{	
	if (count < 0) // base case
		return;
	g.drawEllipse(-.5, -.5, 1, 1, 0.0025f);	
	g.addTransform(radiusTransform_); // push each transform on the stack
	DrawPolarGridCircles(g, count-1);
	g.addTransform(radiusTransform_.inverted()); // pop each transform off the stack
}

void Gridlines::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void Gridlines::DrawGridlines(juce::Graphics & g, float zoomRatio)
{
	auto flipTransform = AffineTransform().scaled(-1, -1);

	float majorGridLineThickness = .005f; //TODO set these better
	float minorGridLineThickness = .001f;

	float width = zoomRatio * 0.5f;
	auto horizontalLine = Line<float>(-width, 0, width, 0);
	auto verticalLine = Line<float>(0, -width, 0, width);

	int numberOfMajorLines = (int)zoomRatio + 1;
	
	int numberOfMinorLines = juce::jmin( (int) (10 / zoomRatio), MAX_MINOR_GRIDLINES);

	float majorGridStep = 0.5f;
	float minorGridStep = majorGridStep / (numberOfMinorLines+1);

	// Draw the gridlines at the origin
	g.drawLine(horizontalLine, majorGridLineThickness);
	g.drawLine(verticalLine, majorGridLineThickness);

	for (int i = 0; i < numberOfMajorLines; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < numberOfMinorLines+1; k++) {
				// shift the lines by the minor grid step
				horizontalLine.applyTransform(AffineTransform::translation(0, minorGridStep));
				verticalLine.applyTransform(AffineTransform::translation(minorGridStep, 0));
				// draw the minor lines
				g.drawLine(horizontalLine, minorGridLineThickness);
				g.drawLine(verticalLine, minorGridLineThickness);
			}
			// Draw the major gridlines
			g.drawLine(horizontalLine, majorGridLineThickness);
			g.drawLine(verticalLine, majorGridLineThickness);
			// transform the lines backward for the next pass
			horizontalLine.applyTransform(AffineTransform::translation(0, -majorGridStep));
			verticalLine.applyTransform(AffineTransform::translation(-majorGridStep, 0));
			// flip the whole context
			g.addTransform(flipTransform);
		}
		// Shift the lines forward the major grid step for the next pass
		horizontalLine.applyTransform(AffineTransform::translation(0, majorGridStep));
		verticalLine.applyTransform(AffineTransform::translation(majorGridStep, 0));
	}
}
