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

#include "sdltSDLManager.h"

#include <stdexcept>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace sdlt;

Manager::Manager()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error{ "SDL could not initialize! SDL Error: " + std::string(SDL_GetError()) };
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		throw std::runtime_error{ "SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()) };
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		throw std::runtime_error{"SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError()) };
	}
}

Manager::~Manager()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}