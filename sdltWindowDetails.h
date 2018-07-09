#pragma once

#include <memory>
#include <SDL.h>

namespace sdlt
{
	class WindowDetails
	{
	public:
		WindowDetails(SDL_Window * window, SDL_Renderer * renderer);
		~WindowDetails();

		SDL_Window * windowPtr;
		SDL_Renderer * rendererPtr;
	};

	using WindowDetailsSPtr = std::shared_ptr<WindowDetails>;
}