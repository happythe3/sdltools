#pragma once

#include <SDL.h>

namespace sdlt
{
	class Colour
	{
	public:
		static SDL_Colour red()   { return SDL_Color{ 0xFF, 0x00, 0x00, 0x00 }; }
		static SDL_Colour green() { return SDL_Color{ 0x00, 0xFF, 0x00, 0x00 }; }
		static SDL_Colour blue()  { return SDL_Color{ 0x00, 0x00, 0xFF, 0x00 }; }

		static SDL_Colour random() 
		{ 
			return SDL_Color{ 
				Uint8(rand() % 0xFF), 
				Uint8(rand() % 0xFF),
				Uint8(rand() % 0xFF),
				0x00
			};
		}
	};
}