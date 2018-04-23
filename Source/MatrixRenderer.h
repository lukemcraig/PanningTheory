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
template<typename MatrixType>
class MatrixRenderer    : public Component
{
public:
	 MatrixRenderer();
	 ~MatrixRenderer();
	
	 void setMatrixToRender(MatrixType* matPointer);

	 void paint (Graphics&) override;
	
	 void resized() override;

private:
	MatrixType* matrixToRender;
	AffineTransform uvTransform_;

	Path getMatrixBracket(bool rightBracket = false);
	void drawBrackets(juce::Graphics & g, float xOffset);
	void drawMatrixValues(juce::Graphics & g, float xOffset);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixRenderer)
};

#include "MatrixRendererImplementation.h"