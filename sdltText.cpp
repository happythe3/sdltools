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

using namespace sdlt;

qdtText::qdtText(int x, int y, qdtFont* font, SDL_Colour colour, std::string text,
	double scaleX, double scaleY, double rotation)
	:RenderNode(x, y, scaleY, scaleY, rotation), m_font{ font }, m_colour{ colour },
	m_text(text), m_regenerate_texture(true), m_texture{ NULL }
{
}

qdtText::~qdtText()
{
	freeOld();
}

void qdtText::updateText(std::string text)
{
	if (m_text.compare(text) != 0)
	{
		// Text has changed
		m_text = text;
		m_regenerate_texture = true;
	}
}

void qdtText::updateColour(SDL_Colour colour)
{
	// Checking if colour has changed
	if (m_colour.r != colour.r || m_colour.g != colour.g || m_colour.b != colour.b || m_colour.a != colour.a)
	{
		m_colour = colour;
		m_regenerate_texture = true;
	}
}

void qdtText::updateTexture(SDL_Renderer * renderer)
{
	if (m_regenerate_texture)
	{
		regenerateTexture(renderer);
	}
}

void qdtText::render(SDL_Renderer * renderer, ParentProperties pProperties)
{
	SDL_Point pos = applyParentPosition(pProperties);

	SDL_Rect render_rect = { pos.x, pos.y, int(mW * pProperties.scaleX * mScale.getX()), 
		int(mH * pProperties.scaleY * mScale.getY()) };

	SDL_RenderCopy(renderer, m_texture, NULL, &render_rect);

	// Done at end so that it is drawn over other items
	RenderNode::render(renderer, pProperties);
}



// ################# //
// Private Functions //
// ################# //

void qdtText::freeOld() 
{
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		mW = 0;
		mH = 0;
	}
}

void qdtText::regenerateTexture(SDL_Renderer * renderer) 
{
	// Clear old texture
	freeOld();

	SDL_Surface* text_surface = TTF_RenderText_Solid(m_font->font(), m_text.c_str(), m_colour);
	if (text_surface == NULL)
	{
		throw;
	}
	else
	{
		// Create texture
		m_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		if (m_texture == NULL)
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

	m_regenerate_texture = false;
}