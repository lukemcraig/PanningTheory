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
#include "MatrixRenderer.h"

//==============================================================================
/**
*/
class PanningTheoryAudioProcessorEditor  : public AudioProcessorEditor,
	private Timer
{
public:
    PanningTheoryAudioProcessorEditor (PanningTheoryAudioProcessor&);
    ~PanningTheoryAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
	
    void resized() override;

	void timerCallback() override;	

private:
	void calculateGains();
	void calculateScaledGains();
	void toggleMode();
	void setModeButtonText();
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PanningTheoryAudioProcessor& processor;
	TextButton subtractButton_;
	bool subtractMode_;

	Gridlines gridlines_;

	MatrixRenderer LMatrixRenderer_;
	MatrixRenderer pMatrixRenderer_;
	MatrixRenderer gainsMatrixRenderer_;
	MatrixRenderer gainsScaledMatrixRenderer_;

	dsp::Matrix<float> p_ = dsp::Matrix<float>(1, 2);
	dsp::Matrix<float> L_ = dsp::Matrix<float>(2, 2);
	dsp::Matrix<float> gains_ = dsp::Matrix<float>(1, 2);
	dsp::Matrix<float> gainsScaled_ = dsp::Matrix<float>(1, 2);

	//File svgFile_;
	//Drawable * svgdrawable_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanningTheoryAudioProcessorEditor)
};
