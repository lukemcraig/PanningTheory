/*
  ==============================================================================

    MathRenderer.cpp
    Created: 22 Apr 2018 8:56:43pm
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

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::dimgrey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);

	// transform into uv coords
	uvTransform_ = AffineTransform();
	auto lb = getLocalBounds();
	// [0.0,height]-> [0.0,1.0]
	uvTransform_ = uvTransform_.scaled(lb.getWidth(), lb.getHeight());
	// center the origin
	g.addTransform(uvTransform_);
	auto centerTransform = AffineTransform().translated(0.5f, 0.5f);
	g.addTransform(centerTransform);

	auto leftBracket = getMatrixBracket();
	auto rightBracket = getMatrixBracket(true);

	float thickness = .05f;
	g.strokePath(leftBracket,PathStrokeType(thickness));
	g.strokePath(rightBracket, PathStrokeType(thickness));

	g.addTransform(centerTransform.inverted());
	//auto offsetCenterTransform = AffineTransform().translated(0, -0.25f);
	//g.addTransform(offsetCenterTransform);
	auto nCol = L_.getNumColumns();
	auto nRow = L_.getNumRows();
	auto height = 1.0f / nRow;
	auto width = 1.0f/ nCol;
	//auto totalWidth = width* nCol;
	for (int col = 0; col < nCol; col++) {	
		for (int row = 0; row < nRow; row++) {	
			//auto textRect = Rectangle<float>(col*width, row*height, width, height);
			auto textRect = Rectangle<float>(col*width, row*height, width, height);
			textRect.reduce(0.1f, 0.1f);
			g.drawRect(textRect, 0.01f);
			g.setFont(0.1f);
			
			g.drawText(String(L_(row, col)), textRect, Justification::centred,true);
		}
	}

	//g.addTransform(uvTransform_.inverted());
}

Path MathRenderer::getMatrixBracket(bool rightBracket) {
	auto linePath = Path();
	float depth = .1f;	

	float xleft = -0.5f;
	float ytop = 0.5f;
	float ybottom = -0.5f;

	linePath.startNewSubPath(xleft + depth, ytop);
	linePath.lineTo(xleft, ytop);
	linePath.lineTo(xleft, ybottom);
	linePath.lineTo(xleft + depth, ybottom);
	if (rightBracket) {
		auto flipTransform = AffineTransform::scale(-1, 1);
		linePath.applyTransform(flipTransform);
	}
	return linePath;
}

void MathRenderer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
