/*
  ==============================================================================

    Gridlines.cpp
    Created: 21 Apr 2018 3:55:02pm
    Author:  Luke

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Gridlines.h"

//==============================================================================
Gridlines::Gridlines()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Gridlines::~Gridlines()
{
}

void Gridlines::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
	// transform into uv coords
	auto cb = g.getClipBounds();
	float zoomRatio = 6;
	float zoomFactor = 1.0f / zoomRatio;
	// [0.0,height]-> [0.0,1.0], make positive y-axis point up
	auto transform = AffineTransform().scaled(cb.getHeight() * zoomFactor, cb.getHeight() * -zoomFactor);
	// center the origin
	transform = transform.translated(cb.getWidth() * 0.5f, cb.getHeight() * 0.5f);
	g.addTransform(transform);

	DrawGridlines(g, zoomRatio);

	g.drawArrow(Line<float>(0, 0, 1, 1), .05, .2f, .2f);
}

void Gridlines::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void Gridlines::DrawGridlines(juce::Graphics & g, float zoomRatio)
{
	auto flipTransform = AffineTransform().scaled(-1, -1);

	float majorGridLineThickness = .005f;
	float minorGridLineThickness = .001f;

	float width = zoomRatio * 0.5f;
	auto horizontalLine = Line<float>(-width, 0, width, 0);
	auto verticalLine = Line<float>(0, -width, 0, width);

	int numberOfMajorLines = (int)zoomRatio;
	int numberOfMinorLines = 5;

	float majorGridStep = 0.5f;
	float minorGridStep = majorGridStep / numberOfMinorLines;

	// Draw the gridlines at the origin
	g.drawLine(horizontalLine, majorGridLineThickness);
	g.drawLine(verticalLine, majorGridLineThickness);

	for (int i = 0; i < numberOfMajorLines; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < numberOfMinorLines; k++) {
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
