/*
  ==============================================================================

    MathRenderer.h
    Created: 24 Apr 2018 12:06:14am
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

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MathRenderer)
};
