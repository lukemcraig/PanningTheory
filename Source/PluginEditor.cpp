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

	zoomSlider_.setSliderStyle(Slider::LinearVertical);
	zoomSlider_.setRange(0, 16, 0);
	zoomSlider_.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	zoomSlider_.setValue(6);	
	addAndMakeVisible(zoomSlider_);

	addAndMakeVisible(gridlines_);
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
	return;
	// transform into uv coords
	auto cb = g.getClipBounds();
	float zoomRatio = zoomSlider_.getValue();
}

void PanningTheoryAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	zoomSlider_.setBounds(0,0,100,400);
	gridlines_.setBounds(110, 0, 600, 600);
}
