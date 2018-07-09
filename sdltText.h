#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "sdltRenderNode.h"
#include "sdltFont.h"

class qdtText :
	public sdlt::RenderNode
{
public:
	qdtText(int x, int y, qdtFont* font, SDL_Colour colour, std::string text = "",
		double scaleX = 1.0, double scaleY = 1.0, double rotation = 0.0);
	~qdtText();

	// Update the text to be rendered
	void updateText(std::string text);
	// Updates the colour that the text is rendered in
	void updateColour(SDL_Colour colour);

	void updateTexture(SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer, ParentProperties pProperties);

private:
	// Fress the old texture
	void freeOld();
	// Regenerates texture
	void regenerateTexture(SDL_Renderer* renderer);

	// Font to use for rendering
	qdtFont* m_font;
	// Colour in which the text should be rendered
	SDL_Colour m_colour;
	// Text that is currently rendered
	std::string m_text;
	// Flag that signals texture regeneration need
	bool m_regenerate_texture;
	// Texture that is being rendered
	SDL_Texture* m_texture;
	
	int mW, mH;
};