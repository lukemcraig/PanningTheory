/*
  ==============================================================================

    Gridlines.h
    Created: 21 Apr 2018 3:55:02pm
    Author:  Luke M Craig

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Gridlines    : public Component
{
public:
    Gridlines();
    ~Gridlines();

	void mouseDown(const MouseEvent & e);

	void mouseDrag(const MouseEvent & e);

    void paint (Graphics&) override;
    void resized() override;

	float zoomRatio_;
	float panAngle_;
private:
	AffineTransform uvTransform_;
	Point<float> dragPoint_;
	int MAX_MINOR_GRIDLINES = 9;
	void DrawGridlines(juce::Graphics & g, float zoomRatio);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Gridlines)
};
