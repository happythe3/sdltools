/*
Copyright 2018 Alexander Shearer

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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