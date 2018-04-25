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

	void mouseUp(const MouseEvent & e) override;

	void mouseDrag(const MouseEvent & e) override;
	void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) override;

    void paint (Graphics&) override;
    void resized() override;

	void setZoomRatio(float newZoomRatio);
	void setPanAngle(float newPanAngle);
	float getPanAngle();

	float g1s_;
	float g2s_;
	float p1_;
	float p2_;

	float l11_;
	float l12_;
	float l21_;
	float l22_;

private:
	AffineTransform identityTransform_;
	AffineTransform uvTransform_;
	AffineTransform radiusTransform_;
	AffineTransform polarLineTransform_;
	float speakerAngle_;
	float speakerAngle2_;

	void DrawSemicircle(juce::Graphics & g);
	void DrawVectors(juce::Graphics & g);
	void DrawSpeaker(juce::Graphics & g, float angle, float x, float y);
	void DrawPolarGridCircles(juce::Graphics & g, int count);
	void DrawGridlines(juce::Graphics & g, float zoomRatio);
	void DrawPolarGrid(juce::Graphics & g);
	void DrawPolarGridLines(juce::Graphics & g, int count, int currentRotation, AffineTransform rotationTransform, int rotationAmount);
	void DrawPolarDegreeText(juce::Graphics & g, int rotationAmount, int currentRotation);

	const int MAX_MINOR_GRIDLINES = 9;
	const float ARROW_WIDTH = 0.1f;
	const float ARROW_LENGTH = 0.1f;

	const float CLICK_EPSILON = 0.75f;
	const float MIN_SPEAKERANGLE = float_Pi / 36.0f;

	const float SPEAKER_SIZE = 0.1f;
	const float SPEAKER_RADIUS = SPEAKER_SIZE / 2.0f;
	const float SPEAKER_OFFSET = 0.08f;

	float zoomRatio_;
	float panAngle_;

	enum ClickableGraphObjects
	{
		nothingId = 0,
		phiVectorId = 1,  
		positiveThetaVectorId = 2,
		negativeThetaVectorId = 3,
	};

	ClickableGraphObjects clickedOn_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Gridlines)
};