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
    setSize (1000, 600);
	setResizable(true, true);	
	setResizeLimits(300, 250, 10000, 10000);

	panAngleSlider_.setSliderStyle(Slider::LinearVertical);
	panAngleSlider_.setRange(-90.0, 90.0, 0.1);
	panAngleSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	panAngleSlider_.setValue(0.0);
	addAndMakeVisible(panAngleSlider_);
	panAngleSlider_.addListener(this);

	g1Slider_.setSliderStyle(Slider::LinearVertical);
	g1Slider_.setRange(0.0, 20.0, 0.01);
	g1Slider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	g1Slider_.setValue(0.0);
	addAndMakeVisible(g1Slider_);

	g2Slider_.setSliderStyle(Slider::LinearVertical);
	g2Slider_.setRange(0.0, 20.0, 0.01);
	g2Slider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	g2Slider_.setValue(0.0);
	addAndMakeVisible(g2Slider_);

	g1sSlider_.setSliderStyle(Slider::LinearVertical);
	g1sSlider_.setRange(0.0, 1.0, 0.01);
	g1sSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	g1sSlider_.setValue(0.0);
	addAndMakeVisible(g1sSlider_);

	g2sSlider_.setSliderStyle(Slider::LinearVertical);
	g2sSlider_.setRange(0.0, 1.0, 0.01);
	g2sSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	g2sSlider_.setValue(0.0);
	addAndMakeVisible(g2sSlider_);

	addAndMakeVisible(gridlines_);

	startTimer(30);
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
	
	panAngleSlider_.setBounds(40, 0, 40, 400);
	g1Slider_.setBounds(80, 0, 60, 400);
	g2Slider_.setBounds(140, 0, 60, 400);

	g1sSlider_.setBounds(200, 0, 60, 400);
	g2sSlider_.setBounds(260, 0, 60, 400);

	gridlines_.setBounds(350, 0, 600, 600);
}

void PanningTheoryAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (slider == &panAngleSlider_) {
		gridlines_.panAngle_ = degreesToRadians(panAngleSlider_.getValue());		
		gridlines_.repaint();
	}
}

void PanningTheoryAudioProcessorEditor::timerCallback()
{
	// TODO use a callback from the grid instead of a timer
	panAngle_ = gridlines_.panAngle_;
	speakerAngle_ = gridlines_.speakerAngle_;
	panAngleSlider_.setValue(radiansToDegrees(panAngle_), dontSendNotification);
	calculateGains();
	g1Slider_.setValue(gains_(0, 0), dontSendNotification);
	g2Slider_.setValue(gains_(0, 1), dontSendNotification);

	calculateScaledGains();
	g1sSlider_.setValue(gainsScaled_(0,0), dontSendNotification);
	g2sSlider_.setValue(gainsScaled_(0,1), dontSendNotification);

	processor.g1s_ = gainsScaled_(0, 0);
	processor.g2s_ = gainsScaled_(0, 1);

	gridlines_.g1s_ = gainsScaled_(0, 0);
	gridlines_.g2s_ = gainsScaled_(0, 1);
}

void PanningTheoryAudioProcessorEditor::calculateScaledGains() {
	float gLength = sqrtf(juce::square(gains_(0, 0)) + juce::square(gains_(0, 1)));
	gainsScaled_ = gains_ * (1.0f/ gLength);
}

void PanningTheoryAudioProcessorEditor::calculateGains() {	
	gains_(0, 0) = calculateLeftGain(panAngle_, speakerAngle_);
	gains_(0, 1) = calculateRightGain(panAngle_, speakerAngle_);	
}

float PanningTheoryAudioProcessorEditor::calculateLeftGain(float phi, float theta)
{
	return (cos(phi)*sin(theta) + sin(phi)*cos(theta)) / (2.0f * cos(theta) * sin(theta));
}

float PanningTheoryAudioProcessorEditor::calculateRightGain(float phi, float theta)
{
	return (cos(phi)*sin(theta) - sin(phi)*cos(theta)) / (2.0f * cos(theta) * sin(theta));
}
