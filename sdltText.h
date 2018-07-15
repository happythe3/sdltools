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
#include "sdltColours.h"

namespace sdlt
{
	class Text :
		public sdlt::RenderNode
	{
	public:
		Text(
			WindowDetailsSPtr windowDetails,
			Vec2D position,
			FontSPtr font,
			SDL_Colour colour,
			std::string text = " ",
			Vec2D scale = Vec2D{ 1, 1 },
			double rotation = 0.0
		);
		~Text();

		void updateText(std::string text);
		void updateColour(SDL_Colour colour);

		void render(ParentProperties pProperties);
	private:
		// Fress the old texture
		void freeOld();
		// Regenerates texture
		void regenerateTexture();

		// Font to use for rendering
		FontSPtr mFont;
		// Colour in which the text should be rendered
		SDL_Colour mColour;
		// Text that is currently rendered
		std::string mText;
		// Flag that signals texture regeneration need
		bool mRegenerateTexture;
		// Texture that is being rendered
		SDL_Texture* mTexture;

		int mW, mH;
	};
}
