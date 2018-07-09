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