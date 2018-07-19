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

ProgressBar::ProgressBar(WindowDetailsSPtr windowDetails)
	:ProgressBar{
	windowDetails,
	sdlt::Vec2D{ 100, 100 },
	sdlt::Vec2D{ 20, 200 },
	{0x00, 0xff, 0x00, 0xff},
	{ 0xff, 0x0, 0x00, 0xff },
	sdlt::Vec2D{ 1, 1 },
	0.0
} {}

ProgressBar::ProgressBar(
	WindowDetailsSPtr windowDetails, 
	Vec2D position,
	Vec2D size,
	SDL_Colour empty, 
	SDL_Colour full, 
	Vec2D scale,
	double rotation)
	:RenderNode{ windowDetails, position, scale, rotation },
	mSize{ size },
	mEmptyCol{ empty }, mFullCol{ full },
	mFillPercent{ 0.0 }
{
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::render(ParentProperties pProperties)
{
	SDL_Point pos = applyParentPosition(pProperties);

	SDL_Rect barRect = {
		pos.x,
		pos.y,
		int(mSize.getX()*pProperties.scaleX * mScale.getX()),
		int(mSize.getY()*pProperties.scaleY * mScale.getY())
	};

	SDL_SetRenderDrawColor(mWindowDetails->rendererPtr, mEmptyCol.r, mEmptyCol.g, mEmptyCol.b, mEmptyCol.a);
	SDL_RenderFillRect(mWindowDetails->rendererPtr, &barRect);

	barRect.w = int(mSize.getX()*pProperties.scaleX * mScale.getX() * mFillPercent);

	SDL_SetRenderDrawColor(mWindowDetails->rendererPtr, mFullCol.r, mFullCol.g, mFullCol.b, mFullCol.a);
	SDL_RenderFillRect(mWindowDetails->rendererPtr, &barRect);
}

void ProgressBar::setPercentage(double newPercentage)
{
	mFillPercent = newPercentage;

	if (mFillPercent < 0.0)
	{
		mFillPercent = 0.0;
	}
	else if (mFillPercent > 1.0)
	{
		mFillPercent = 1.0;
	}
}

void ProgressBar::updateSize(int w, int h)
{
	mSize.setX(w);
	mSize.setY(h);
}

void ProgressBar::updateSize(Vec2D size)
{
	mSize = size;
}