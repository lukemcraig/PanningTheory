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
    setSize (400, 300);
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

	auto transform = AffineTransform().scaled(150, -150).translated(200,150);
	g.addTransform(transform);

	float majorGridLineThickness = .005f;
	float minorGridLineThickness = .001f;
	auto horizontalLine = Line<float>(-1,-1,1,-1);
	auto verticalLine = Line<float>(-1, -1, -1, 1);
	int numberOfMajorLines = 4;
	int numberOfMinorLines = 4;
	for (int i = 0; i < numberOfMajorLines; i++) {
		g.drawLine(horizontalLine, majorGridLineThickness);
		for (int i = 0; i < numberOfMinorLines; i++) {
			horizontalLine.applyTransform(AffineTransform::translation(0, 0.5f / numberOfMinorLines));
			g.drawLine(horizontalLine, minorGridLineThickness);
		}		

		g.drawLine(verticalLine, majorGridLineThickness);
		for (int i = 0; i < numberOfMinorLines; i++) {
			verticalLine.applyTransform(AffineTransform::translation(0.5f / numberOfMinorLines, 0));			
			g.drawLine(verticalLine, minorGridLineThickness);
		}
	}	
	g.drawLine(horizontalLine, majorGridLineThickness);
	g.drawLine(verticalLine, majorGridLineThickness);

	g.drawArrow(Line<float>(0, 0, 1, 1), .05,.2f,.2f);
}

void PanningTheoryAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
