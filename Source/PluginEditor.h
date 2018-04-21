/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PanningTheoryAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PanningTheoryAudioProcessorEditor (PanningTheoryAudioProcessor&);
    ~PanningTheoryAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
	void DrawGridlines(juce::Graphics & g, float zoomRatio);
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PanningTheoryAudioProcessor& processor;

	Slider zoomSlider_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanningTheoryAudioProcessorEditor)
};
