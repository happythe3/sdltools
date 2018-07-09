#pragma once

#include <SDL.h>

namespace sdlt
{

	class RenderItem
	{
	public:
		RenderItem();
		virtual ~RenderItem();

		virtual void render(SDL_Renderer* renderer);
	};

}