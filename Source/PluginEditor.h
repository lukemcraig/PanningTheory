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
	public Slider::Listener
{
public:
    PanningTheoryAudioProcessorEditor (PanningTheoryAudioProcessor&);
    ~PanningTheoryAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
	
    void resized() override;

	void sliderValueChanged(Slider * slider);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PanningTheoryAudioProcessor& processor;
	Gridlines gridlines_;
	Slider zoomSlider_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanningTheoryAudioProcessorEditor)
};
