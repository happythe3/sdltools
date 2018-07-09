#pragma once

#include "sdltRenderNode.h"


enum BarType {
	BarHorizontal,
	BarVertical
};

class qdtProgressBar :
	public sdlt::RenderNode
{
public:
	qdtProgressBar(int x, int y, int w, int h, SDL_Colour empty, SDL_Colour full, BarType type = BarHorizontal);
	~qdtProgressBar();

	void render(SDL_Renderer* renderer, ParentProperties pProperties);

	void setPercentage(double newPercentage);

	void updateSize(int w, int h);
private:
	int mW;
	int mH;

	SDL_Colour mEmptyCol;
	SDL_Colour mFullCol;

	BarType mType;

	double mFillPercent;
};