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
