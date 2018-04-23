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
#include "MathRenderer.h"

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
	void calculateScaledGains();
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PanningTheoryAudioProcessor& processor;
	Gridlines gridlines_;
	MathRenderer mathRenderer_;

	Slider panAngleSlider_;

	Slider g1Slider_;
	Slider g2Slider_;
	Slider g1sSlider_;
	Slider g2sSlider_;
	float panAngle_;

	dsp::Matrix<float> p_ = dsp::Matrix<float>(1, 2);
	dsp::Matrix<float> L_ = dsp::Matrix<float>(2, 2);
	dsp::Matrix<float> gains_ = dsp::Matrix<float>(1, 2);
	dsp::Matrix<float> gainsScaled_ = dsp::Matrix<float>(1, 2);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanningTheoryAudioProcessorEditor)
};
