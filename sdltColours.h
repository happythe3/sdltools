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

#include <SDL.h>

namespace sdlt
{
	class Colour
	{
	public:
		static SDL_Colour red()   { return SDL_Color{ 0xFF, 0x00, 0x00, 0x00 }; }
		static SDL_Colour green() { return SDL_Color{ 0x00, 0xFF, 0x00, 0x00 }; }
		static SDL_Colour blue()  { return SDL_Color{ 0x00, 0x00, 0xFF, 0x00 }; }
		static SDL_Colour orange() { return SDL_Color{ 0xFF, 0xa5, 0x00, 0x00 }; }


		static SDL_Colour random() 
		{ 
			return SDL_Color{ 
				Uint8(rand() % 0xFF), 
				Uint8(rand() % 0xFF),
				Uint8(rand() % 0xFF),
				0x00
			};
		}

		static bool equal(const SDL_Colour &c1, const SDL_Colour &c2)
		{
			return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
		}
	};

	
}