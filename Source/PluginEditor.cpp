/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PanningTheoryAudioProcessorEditor::PanningTheoryAudioProcessorEditor (PanningTheoryAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	subtractMode_ = false;

    setSize (1000, 750);
	setResizable(true, true);	
	setResizeLimits(300, 250, 10000, 10000);

	addAndMakeVisible(gridlines_);
	
	LMatrixRenderer_.setMatrixToRender(&L_);
	addAndMakeVisible(LMatrixRenderer_);
	pMatrixRenderer_.setMatrixToRender(&p_);
	addAndMakeVisible(pMatrixRenderer_);
	gainsMatrixRenderer_.setMatrixToRender(&gains_);
	addAndMakeVisible(gainsMatrixRenderer_);
	gainsScaledMatrixRenderer_.setMatrixToRender(&gainsScaled_);
	addAndMakeVisible(gainsScaledMatrixRenderer_);

	/*svgFile_ = File("C:\\Users\\Luke\\Downloads\\gainlatex.svg");
	svgdrawable_ = Drawable::createFromSVGFile(svgFile_);*/

	setModeButtonText();
	subtractButton_.onClick = [this] { toggleMode(); };
	addAndMakeVisible(subtractButton_);	

	startTimer(30);
}

PanningTheoryAudioProcessorEditor::~PanningTheoryAudioProcessorEditor()
{
	//svgdrawable_->~Drawable();
}

//==============================================================================
void PanningTheoryAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
	auto destArea = Rectangle< float >(getLocalBounds().toFloat());

	//svgdrawable_->drawWithin(g, destArea, RectanglePlacement::xLeft,0.5f);
}

void PanningTheoryAudioProcessorEditor::resized()
{
	auto area = getLocalBounds();
	area.reduce(10, 10);
	gridlines_.setBounds(area.removeFromTop(area.getHeight() * 0.5f));
	
	auto subtractButtonArea = area.removeFromTop(50).removeFromRight(100).reduced(0, 10);
	subtractButton_.setBounds(subtractButtonArea);

	auto matrixRow = area.removeFromTop(area.getHeight() * 0.5f).reduced(0,10);
	auto matrixRowElement = matrixRow.proportionOfWidth(1.0f/3.0f);
	gainsMatrixRenderer_.setBounds(matrixRow.removeFromLeft(matrixRowElement).reduced(10.0f).reduced(20.0f, 40.0f));
	pMatrixRenderer_.setBounds(matrixRow.removeFromLeft(matrixRowElement).reduced(10.0f).reduced(20.0f, 40.0f));
	LMatrixRenderer_.setBounds(matrixRow.removeFromLeft(matrixRowElement).reduced(10.0f));
	
	auto solutionRow = area;
	gainsScaledMatrixRenderer_.setBounds(solutionRow.removeFromLeft(matrixRowElement).reduced(10.0f).reduced(20.0f, 40.0f));
}

void PanningTheoryAudioProcessorEditor::timerCallback()
{
	// TODO use a callback from the grid instead of a timer
	//panAngle_ = gridlines_.getPanAngle();
	p_(0, 0) = gridlines_.p1_;
	p_(0, 1) = gridlines_.p2_;

	L_(0, 0) = gridlines_.l11_;
	L_(0, 1) = gridlines_.l12_;
	L_(1, 0) = gridlines_.l21_;
	L_(1, 1) = gridlines_.l22_;

	//panAngleSlider_.setValue(radiansToDegrees(panAngle_), dontSendNotification);
	calculateGains();
	/*g1Slider_.setValue(gains_(0, 0), dontSendNotification);
	g2Slider_.setValue(gains_(0, 1), dontSendNotification);*/

	calculateScaledGains();
	/*g1sSlider_.setValue(gainsScaled_(0,0), dontSendNotification);
	g2sSlider_.setValue(gainsScaled_(0,1), dontSendNotification);*/

	processor.g1s_ = gainsScaled_(0, 0);
	processor.g2s_ = gainsScaled_(0, 1);

	gridlines_.g1s_ = gainsScaled_(0, 0);
	gridlines_.g2s_ = gainsScaled_(0, 1);

	LMatrixRenderer_.repaint();
	pMatrixRenderer_.repaint();
	gainsMatrixRenderer_.repaint();
	gainsScaledMatrixRenderer_.repaint();
}

void PanningTheoryAudioProcessorEditor::calculateScaledGains() {
	float gLength = sqrtf(juce::square(gains_(0, 0)) + juce::square(gains_(0, 1)));
	gainsScaled_ = gains_ * (1.0f/ gLength);
}

void PanningTheoryAudioProcessorEditor::toggleMode()
{
	subtractMode_ = !subtractMode_;
	setModeButtonText();
}

void PanningTheoryAudioProcessorEditor::setModeButtonText()
{
	subtractButton_.setButtonText(subtractMode_ ? "Pan Mode" : "Remove Mode");
	if(subtractMode_)
		getLookAndFeel().setColour(ResizableWindow::backgroundColourId,Colour::fromRGB(56, 51, 37));
	else
		getLookAndFeel().setColour(ResizableWindow::backgroundColourId, Colour::fromRGB(50,62,68));
	repaint();
}

void PanningTheoryAudioProcessorEditor::calculateGains() {
	auto determinant = L_(0, 0)*L_(1, 1) - L_(1, 0)*L_(0, 1);
	auto inverseDeterminant = 1.0f / determinant;
	auto inverseL = dsp::Matrix<float>(L_);	
	inverseL(0, 0) = L_(1,1);
	inverseL(1, 1) = L_(0, 0);
	inverseL(0, 1) *= -1;
	inverseL(1, 0) *= -1;
	gains_ = p_ * inverseDeterminant * inverseL;	
}
