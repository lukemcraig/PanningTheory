/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Gridlines.h"

//==============================================================================
/**
*/
class PanningTheoryAudioProcessorEditor  : public AudioProcessorEditor,
	public Slider::Listener, private Timer
{
public:
    PanningTheoryAudioProcessorEditor (PanningTheoryAudioProcessor&);
    ~PanningTheoryAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
	
    void resized() override;

	void sliderValueChanged(Slider * slider);
	void timerCallback() override;	

private:
	void calculateGains();
	static float calculateLeftGain(float phi, float theta);
	static float calculateRightGain(float phi, float theta);
	void calculateScaledGains();
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PanningTheoryAudioProcessor& processor;
	Gridlines gridlines_;
	Slider panAngleSlider_;

	Slider g1Slider_;
	Slider g2Slider_;
	Slider g1sSlider_;
	Slider g2sSlider_;
	const float speakerAngle_ = 45.0f;
	float panAngle_;
	float g1_;
	float g2_;
	float g1s_;
	float g2s_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanningTheoryAudioProcessorEditor)
};
