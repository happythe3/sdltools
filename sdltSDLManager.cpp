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