/*
  ==============================================================================

    MatrixRendererImplementation.h
    Created: 22 Apr 2018 8:56:43pm
    Author:  Luke

  ==============================================================================
*/



#include "../JuceLibraryCode/JuceHeader.h"
#include "MatrixRenderer.h"
//==============================================================================
MatrixRenderer::MatrixRenderer()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}


MatrixRenderer::~MatrixRenderer()
{
}


void MatrixRenderer::paint (Graphics& g)
{
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::white);

	auto lb = getLocalBounds();
	// transform into uv coords
	uvTransform_ = AffineTransform();
	// [0.0,height]-> [0.0,1.0]
	uvTransform_ = uvTransform_.scaled(lb.getWidth(), lb.getHeight());
	g.addTransform(uvTransform_);
	auto aspect = ((float)lb.getWidth() / lb.getHeight());
	//aspect = 1.0f;
	//auto xOffset = 0.5f * aspect;
	auto xOffset = 0.5f;
	drawBrackets(g, xOffset);
	drawMatrixValues(g, xOffset, aspect);
}


void MatrixRenderer::drawBrackets(juce::Graphics & g, float xOffset)
{
	// center the origin
	auto centerTransform = AffineTransform().translated(xOffset, 0.5f);
	g.addTransform(centerTransform);

	auto leftBracket = getMatrixBracket();
	auto rightBracket = getMatrixBracket(true);

	float thickness = .025f;
	g.strokePath(leftBracket, PathStrokeType(thickness));
	g.strokePath(rightBracket, PathStrokeType(thickness));

	g.addTransform(centerTransform.inverted());
}


void MatrixRenderer::drawMatrixValues(juce::Graphics & g, float xOffset, float aspect)
{
	auto offsetCenterTransform = AffineTransform().translated(xOffset-.5f, 0);
	g.addTransform(offsetCenterTransform);

	auto nCol = matrixToRender_->getNumColumns();
	auto nRow = matrixToRender_->getNumRows();
	auto height = 1.0f / nRow;
	auto width = 1.0f / nCol;

	for (int col = 0; col < nCol; col++) {
		for (int row = 0; row < nRow; row++) {
			auto cellTrans = AffineTransform().scaled(width, height).translated(col*width, row*height);
			g.addTransform(cellTrans);

			auto cellShrink = AffineTransform().scaled(.5f,.5f);
			g.addTransform(cellShrink);
			auto textRect = Rectangle<float>(0.0f, 0.0f, 1.0f, 1.0f);
			g.setColour(Colours::aliceblue);
			g.drawRect(textRect, 0.01f);
			//Font newFont(1.0f);
			//newFont.setHeightWithoutChangingWidth(.25f);	
			//.translated(.25f, 0)
			auto textCorrection = AffineTransform().scaled(height/aspect, width);
			g.addTransform(textCorrection);
			g.setColour(Colours::deeppink);
			g.drawRect(textRect, 0.01f);
			g.setColour(Colours::white);
			g.setFont(0.5f);
			g.drawText(String(matrixToRender_->operator()(row, col), 2), textRect, Justification::centred, true);
			
			g.addTransform(textCorrection.inverted());
			g.addTransform(cellShrink.inverted());
			g.addTransform(cellTrans.inverted());
		}
	}
	g.addTransform(offsetCenterTransform.inverted());
}


Path MatrixRenderer::getMatrixBracket(bool rightBracket) {
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


void MatrixRenderer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void MatrixRenderer::setMatrixToRender(dsp::Matrix<float>* matrixToRender)
{
	matrixToRender_ = matrixToRender;
}


