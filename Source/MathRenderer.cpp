/*
  ==============================================================================

    MathRenderer.cpp
    Created: 24 Apr 2018 12:06:14am
    Author:  Luke

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MathRenderer.h"

//==============================================================================
MathRenderer::MathRenderer()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MathRenderer::~MathRenderer()
{
}

void MathRenderer::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("MathRenderer", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void MathRenderer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
