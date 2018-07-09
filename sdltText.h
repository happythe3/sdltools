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