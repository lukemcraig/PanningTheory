/*
  ==============================================================================

    MatrixRenderer.h
    Created: 22 Apr 2018 8:56:43pm
    Author:  Luke

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MatrixRenderer    : public Component
{
public:
    MatrixRenderer();
    ~MatrixRenderer();
	dsp::Matrix<float> L_ = dsp::Matrix<float>(2, 2);
    void paint (Graphics&) override;

	void drawBrackets(juce::Graphics & g, float xOffset);

	void drawMatrixValues(juce::Graphics & g, float xOffset);
	
    void resized() override;

private:
	Path getMatrixBracket(bool rightBracket = false);

	AffineTransform uvTransform_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixRenderer)
};
