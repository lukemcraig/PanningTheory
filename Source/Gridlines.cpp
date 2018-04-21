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
	//addAndMakeVisible(knob_);
	zoomRatio_ = 0;
	panAngle_ = 0;
}

Gridlines::~Gridlines()
{
}



void Gridlines::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (Colours::white);

	auto cb = g.getClipBounds();
	float zoomFactor = 1.0f / zoomRatio_;

	// transform into uv coords
	// [0.0,height]-> [0.0,1.0], make positive y-axis point up
	auto transform = AffineTransform().scaled(cb.getHeight() * zoomFactor, cb.getHeight() * -zoomFactor);
	// center the origin
	transform = transform.translated(cb.getWidth() * 0.5f, cb.getHeight() * 0.5f);
	g.addTransform(transform);

	DrawGridlines(g, zoomRatio_);

	g.drawArrow(Line<float>(0, 0, cos(panAngle_), sin(panAngle_)), .05, .2f, .2f);
}

void Gridlines::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
	
	//knob_.setBounds(10, 10, 40, 40);
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
