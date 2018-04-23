/*
  ==============================================================================

    MathRenderer.h
    Created: 22 Apr 2018 8:56:43pm
    Author:  Luke

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MathRenderer    : public Component
{
public:
    MathRenderer();
    ~MathRenderer();
	dsp::Matrix<float> L_ = dsp::Matrix<float>(2, 2);
    void paint (Graphics&) override;

	void drawMatrixValues(juce::Graphics & g, float xOffset);
	
    void resized() override;

private:
	Path getMatrixBracket(bool rightBracket = false);

	AffineTransform uvTransform_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MathRenderer)
};
