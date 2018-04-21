/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PanningTheoryAudioProcessorEditor::PanningTheoryAudioProcessorEditor (PanningTheoryAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
	setResizable(true, true);	
	setResizeLimits(300, 250, 10000, 10000);
}

PanningTheoryAudioProcessorEditor::~PanningTheoryAudioProcessorEditor()
{
}

//==============================================================================
void PanningTheoryAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
	// transform into uv coords
	auto cb = g.getClipBounds();
	//TODO parameterize zoom
	auto transform = AffineTransform().scaled(cb.getHeight()/4, cb.getHeight() / -4).translated(cb.getWidth() / 2, cb.getHeight() / 2);
	g.addTransform(transform);
	
	DrawGridlines(g);

	g.drawArrow(Line<float>(0, 0, 1, 1), .05,.2f,.2f);
}

void PanningTheoryAudioProcessorEditor::DrawGridlines(juce::Graphics & g)
{
	auto flipTransform = AffineTransform().scaled(-1, -1);

	float majorGridLineThickness = .005f;
	float minorGridLineThickness = .001f;

	float width = 3; //TODO base on zoom
	auto horizontalLine = Line<float>(-width, 0, width, 0);
	auto verticalLine = Line<float>(0, -width, 0, width);

	int numberOfMajorLines = 5; //TODO base on zoom
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

void PanningTheoryAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

}
