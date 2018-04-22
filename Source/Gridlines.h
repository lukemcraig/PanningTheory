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

	void mouseDown(const MouseEvent & e) override;

	void mouseDrag(const MouseEvent & e) override;
	void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) override;

    void paint (Graphics&) override;
	void DrawPolarGridCircles(juce::Graphics & g, int count);
    void resized() override;

	// TODO getters, setters
	float zoomRatio_;
	float panAngle_;
	float speakerAngle_ = float_Pi / 4.0f;

private:
	AffineTransform uvTransform_;
	AffineTransform radiusTransform_;
	AffineTransform polarLineTransform_;
	Point<float> dragPoint_;
	void DrawGridlines(juce::Graphics & g, float zoomRatio);
	void DrawPolarGrid(juce::Graphics & g);

	void DrawPolarGridLines(juce::Graphics & g, int count);

	const int MAX_MINOR_GRIDLINES = 9;
	const float ARROW_WIDTH = 0.1f;
	const float ARROW_LENGTH = 0.1f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Gridlines)
};