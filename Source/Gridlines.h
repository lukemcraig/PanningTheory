/*
  ==============================================================================

    Gridlines.h
    Created: 21 Apr 2018 3:55:02pm
    Author:  Luke M Craig

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TestCircle.h"

//==============================================================================
/*
*/
class Gridlines    : public Component
{
public:
    Gridlines();
    ~Gridlines();

    void paint (Graphics&) override;
    void resized() override;

	float zoomRatio_;
	float panAngle_;
private:
	

	int MAX_MINOR_GRIDLINES = 9;
	void DrawGridlines(juce::Graphics & g, float zoomRatio);

	TestCircle knob_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Gridlines)
};
