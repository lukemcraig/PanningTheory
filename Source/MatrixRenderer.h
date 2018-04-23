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
	
	void setMatrixToRender(dsp::Matrix<float>* matPointer);

    void paint (Graphics&) override;
	
    void resized() override;

private:
	dsp::Matrix<float>* L_;
	AffineTransform uvTransform_;

	Path getMatrixBracket(bool rightBracket = false);	
	void drawBrackets(juce::Graphics & g, float xOffset);
	void drawMatrixValues(juce::Graphics & g, float xOffset);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixRenderer)
};
