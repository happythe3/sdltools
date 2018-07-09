#include "sdltSquare.h"
#include <iostream>

using namespace sdlt;



Square::Square(WindowDetailsSPtr window, int x, int y, int size, SDL_Colour colour,
	double scaleX, double scaleY, double rotation)
	:RenderNode(window, Position2D{ x, y }, Vec2D{ scaleX, scaleY } , rotation), mSize{ size }, mColour{ colour }
{
}

Square::~Square()
{
}

void Square::render(ParentProperties pProperties)
{
	SDL_SetRenderDrawColor(mWindowDetails->rendererPtr, 
		mColour.r, mColour.g, mColour.b, mColour.a);

	SDL_Point pos = applyParentPosition(pProperties);

	SDL_Rect render_rect = {
		pos.x,
		pos.y,
		int(mSize*pProperties.scaleX * mScale.getX()),
		int(mSize*pProperties.scaleY * mScale.getY())
	};


	if (SDL_RenderFillRect(mWindowDetails->rendererPtr, &render_rect) != 0)
	{
		std::cout << "Square::render || SDL error" << std::endl;
	}
}
