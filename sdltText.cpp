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

#include "sdltText.h"
#include <exception>

using namespace sdlt;

sdlt::Text::Text(
	WindowDetailsSPtr windowDetails,
	Vec2D position, 
	FontSPtr font, 
	SDL_Colour colour,
	std::string text, 
	Vec2D scale, 
	double rotation)
	:RenderNode{ windowDetails, position, scale, rotation },
	mFont{ font }, mColour{ colour }, mText{ text },
	mRegenerateTexture{ true },
	mTexture{ NULL }
{
}

Text::~Text()
{
	freeOld();
}

void Text::updateText(std::string text)
{
	if (mText.compare(text) != 0)
	{
		mText = text;
		mRegenerateTexture = true;
	}
}

void Text::updateColour(SDL_Colour colour)
{
	if (!Colour::equal(mColour, colour))
	{
		mColour = colour;
		mRegenerateTexture = true;
	}
}

void Text::render(ParentProperties pProperties)
{
	if (mRegenerateTexture)
	{
		regenerateTexture();
	}

	SDL_Point pos = applyParentPosition(pProperties);

	SDL_Rect render_rect = { pos.x, pos.y, int(mW * pProperties.scaleX * mScale.getX()), 
		int(mH * pProperties.scaleY * mScale.getY()) };

	SDL_RenderCopy(mWindowDetails->rendererPtr, mTexture, NULL, &render_rect);

	// Done at end so that it is drawn over other items
	RenderNode::render(pProperties);
}



// ################# //
// Private Functions //
// ################# //

void Text::freeOld() 
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mW = 0;
		mH = 0;
	}
}

void Text::regenerateTexture() 
{
	// Clear old texture
	freeOld();

	if (mText.length() == 0)
	{
		// Can't have zero length string
		mText = " ";
	}

	SDL_Surface* text_surface = TTF_RenderText_Solid(mFont->font(), mText.c_str(), mColour);
	if (text_surface == NULL)
	{
		throw std::exception(TTF_GetError());
	}
	else
	{
		// Create texture
		mTexture = SDL_CreateTextureFromSurface(mWindowDetails->rendererPtr, text_surface);
		if (mTexture == NULL)
		{
			throw;
		}
		else
		{
			mH = text_surface->h;
			mW = text_surface->w;
		}
	}

	SDL_FreeSurface(text_surface);

	mRegenerateTexture = false;
}