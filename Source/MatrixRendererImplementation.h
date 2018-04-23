/*
  ==============================================================================

    MatrixRendererImplementation.h
    Created: 22 Apr 2018 8:56:43pm
    Author:  Luke

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
template<typename MatrixType>
MatrixRenderer<MatrixType>::MatrixRenderer()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

template<typename MatrixType>
MatrixRenderer<MatrixType>::~MatrixRenderer()
{
}

template<typename MatrixType>
void MatrixRenderer<MatrixType>::setMatrixToRender(MatrixType* matPointer)
{
	matrixToRender = matPointer;
}

template<typename MatrixType>
void MatrixRenderer<MatrixType>::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

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

template<typename MatrixType>
void MatrixRenderer<MatrixType>::drawBrackets(juce::Graphics & g, float xOffset)
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

template<typename MatrixType>
void MatrixRenderer<MatrixType>::drawMatrixValues(juce::Graphics & g, float xOffset, float aspect)
{
	auto offsetCenterTransform = AffineTransform().translated(xOffset-.5f, 0);
	g.addTransform(offsetCenterTransform);

	auto nCol = matrixToRender->getNumColumns();
	auto nRow = matrixToRender->getNumRows();
	auto height = 1.0f / nRow;
	auto width = 1.0f / nCol;


	for (int col = 0; col < nCol; col++) {
		for (int row = 0; row < nRow; row++) {
			auto cellTrans = AffineTransform().scaled(width, height).translated(col*width, row*height);
			g.addTransform(cellTrans);

			auto cellShrink = AffineTransform().scaled(1,1);
			g.addTransform(cellShrink);
			auto textRect = Rectangle<float>(0.0f, 0.0f, 1.0f, 1.0f);
			g.drawRect(textRect, 0.01f);
			//Font newFont(1.0f);
			//newFont.setHeightWithoutChangingWidth(.25f);	

			auto textCorrection = AffineTransform().scaled(1.0f/aspect, 1);
			g.addTransform(textCorrection);
			g.setFont(0.5f);
			g.drawText(String(matrixToRender->operator()(row, col), 2), textRect, Justification::horizontallyCentred, true);
			
			g.addTransform(textCorrection.inverted());
			g.addTransform(cellShrink.inverted());
			g.addTransform(cellTrans.inverted());
		}
	}
	g.addTransform(offsetCenterTransform.inverted());
}

template<typename MatrixType>
Path MatrixRenderer<MatrixType>::getMatrixBracket(bool rightBracket) {
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

template<typename MatrixType>
void MatrixRenderer<MatrixType>::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}