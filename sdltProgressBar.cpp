#include "sdltProgressBar.h"

using namespace sdlt;

qdtProgressBar::qdtProgressBar(int x, int y, int w, int h, SDL_Colour empty, 
	SDL_Colour full, BarType type)
	:RenderNode(x, y)
{
	mW = w;
	mH = h;
	
	mEmptyCol = empty;
	mFullCol = full;

	mType = type;

	mFillPercent = 0.0;
}

qdtProgressBar::~qdtProgressBar()
{

}


void qdtProgressBar::render(SDL_Renderer * renderer, ParentProperties pProperties)
{
	SDL_Point pos = applyParentPosition(pProperties);

	SDL_Rect barRect = {
		pos.x,
		pos.y,
		int(mW*pProperties.scaleX * mScale.getX()),
		int(mH*pProperties.scaleY * mScale.getY())
	};

	SDL_SetRenderDrawColor(renderer, mEmptyCol.r, mEmptyCol.g, mEmptyCol.b, mEmptyCol.a);
	SDL_RenderFillRect(renderer, &barRect);

	switch (mType)
	{
	case BarHorizontal:
		barRect.w = int(mW*pProperties.scaleX * mScale.getX() * mFillPercent);
		break;
	case BarVertical:
		barRect.h = int(mH*pProperties.scaleY * mScale.getY() * mFillPercent);
		break;
	default:
		throw;
		break;
	}

	SDL_SetRenderDrawColor(renderer, mFullCol.r, mFullCol.g, mFullCol.b, mFullCol.a);
	SDL_RenderFillRect(renderer, &barRect);
}

void qdtProgressBar::setPercentage(double newPercentage)
{
	mFillPercent = newPercentage;

	if (mFillPercent < 0.0)
	{
		mFillPercent = 0.0;
	}
}

void qdtProgressBar::updateSize(int w, int h)
{
	mW = w;
	mH = h;
}