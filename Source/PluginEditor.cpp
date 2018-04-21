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
	zoomSlider_.setRange(DBL_TRUE_MIN, 16.0, 0);
	zoomSlider_.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	zoomSlider_.setValue(2.0);	
	addAndMakeVisible(zoomSlider_);
	zoomSlider_.addListener(this);

	panAngleSlider_.setSliderStyle(Slider::LinearVertical);
	panAngleSlider_.setRange(-90.0, 90.0, 0.1);
	panAngleSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	panAngleSlider_.setValue(0.0);
	addAndMakeVisible(panAngleSlider_);
	panAngleSlider_.addListener(this);

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
}

void PanningTheoryAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	zoomSlider_.setBounds(0,0,20,400);
	panAngleSlider_.setBounds(40, 0, 40, 400);
	gridlines_.setBounds(110, 0, 600, 600);
}

void PanningTheoryAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (slider == &zoomSlider_) {
		gridlines_.zoomRatio_ = zoomSlider_.getValue();
		gridlines_.repaint();
	}
	if (slider == &panAngleSlider_) {
		gridlines_.panAngle_ = juce::degreesToRadians(panAngleSlider_.getValue());		
		gridlines_.repaint();
	}
}
