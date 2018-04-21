/*
  ==============================================================================

    Gridlines.h
    Created: 21 Apr 2018 3:55:02pm
    Author:  Luke

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

    void paint (Graphics&) override;
    void resized() override;

	float zoomRatio_;

private:
	void DrawGridlines(juce::Graphics & g, float zoomRatio);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Gridlines)
};
