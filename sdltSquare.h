#pragma once
#include "sdltRenderNode.h"

namespace sdlt
{

	class Square :
		public RenderNode
	{
	public:
		Square(WindowDetailsSPtr window, int x, int y, int size, SDL_Colour colour,
			double scaleX = 1.0, double scaleY = 1.0, double rotation = 0.0);
		~Square();

		void render(ParentProperties pProperties);

	private:
		int mSize;
		SDL_Colour mColour;
	};

}