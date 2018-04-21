/*
  ==============================================================================

    TestCircle.h
    Created: 21 Apr 2018 5:54:04pm
    Author:  Luke M Craig

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TestCircle    : public Component
{
public:
    TestCircle()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
    }

    ~TestCircle()
    {
    }

    void paint (Graphics& g) override
    {      
        g.setColour (Colours::grey);        
		g.fillEllipse(getLocalBounds().toFloat());        
    }

    void resized() override
    {
        constrainer.setMinimumOnscreenAmounts(getHeight(), getWidth(), getHeight(), getWidth());
    }

	void mouseDown(const MouseEvent& e) override
	{
		// Prepares our dragger to drag this Component
		dragger.startDraggingComponent(this, e);
	}

	void mouseDrag(const MouseEvent& e) override
	{
		// Moves this Component according to the mouse drag event and applies our constraints to it
		dragger.dragComponent(this, e, &constrainer);
	}

private:
	ComponentDragger dragger;
	ComponentBoundsConstrainer constrainer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestCircle)
};
