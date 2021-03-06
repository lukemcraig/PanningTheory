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
	
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 750);
	setResizable(true, true);	
	setResizeLimits(300, 250, 10000, 10000);

	//panAngleSlider_.setSliderStyle(Slider::LinearVertical);
	//panAngleSlider_.setRange(-90.0, 90.0, 0.1);
	//panAngleSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	//panAngleSlider_.setValue(0.0);
	//addAndMakeVisible(panAngleSlider_);
	//panAngleSlider_.addListener(this);

	//g1Slider_.setSliderStyle(Slider::LinearVertical);
	//g1Slider_.setRange(0.0, 20.0, 0.01);
	//g1Slider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	//g1Slider_.setValue(0.0);
	//addAndMakeVisible(g1Slider_);

	//g2Slider_.setSliderStyle(Slider::LinearVertical);
	//g2Slider_.setRange(0.0, 20.0, 0.01);
	//g2Slider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	//g2Slider_.setValue(0.0);
	//addAndMakeVisible(g2Slider_);

	//g1sSlider_.setSliderStyle(Slider::LinearVertical);
	//g1sSlider_.setRange(0.0, 1.0, 0.01);
	//g1sSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	//g1sSlider_.setValue(0.0);
	//addAndMakeVisible(g1sSlider_);

	//g2sSlider_.setSliderStyle(Slider::LinearVertical);
	//g2sSlider_.setRange(0.0, 1.0, 0.01);
	//g2sSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 60);
	//g2sSlider_.setValue(0.0);
	//addAndMakeVisible(g2sSlider_);

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
	
	/*panAngleSlider_.setBounds(40, 0, 40, 400);
	g1Slider_.setBounds(80, 0, 60, 400);
	g2Slider_.setBounds(140, 0, 60, 400);

	g1sSlider_.setBounds(200, 0, 60, 400);
	g2sSlider_.setBounds(260, 0, 60, 400);	
	*/
	auto matrixRow = area.removeFromTop(area.getHeight() * 0.5f).reduced(0,10);
	auto matrixRowElement = matrixRow.proportionOfWidth(1.0f/3.0f);
	gainsMatrixRenderer_.setBounds(matrixRow.removeFromLeft(matrixRowElement).reduced(10.0f).reduced(20.0f, 40.0f));
	pMatrixRenderer_.setBounds(matrixRow.removeFromLeft(matrixRowElement).reduced(10.0f).reduced(20.0f, 40.0f));
	LMatrixRenderer_.setBounds(matrixRow.removeFromLeft(matrixRowElement).reduced(10.0f));
	auto solutionRow = area;
	gainsScaledMatrixRenderer_.setBounds(solutionRow.removeFromLeft(matrixRowElement).reduced(10.0f).reduced(20.0f, 40.0f));

}

void PanningTheoryAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	//if (slider == &panAngleSlider_) {
	//	gridlines_.setPanAngle(degreesToRadians(panAngleSlider_.getValue()));		
	//	gridlines_.repaint();
	//}
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
