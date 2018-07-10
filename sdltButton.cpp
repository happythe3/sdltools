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

#include "sdltButton.h"

using namespace sdlt;

sdlt::Button::Button(
	std::string name, 
	ButtonType type,
	int w, int h,
	WindowDetailsSPtr windowDetails, 
	Vec2D position, 
	Vec2D scale, 
	double rotation)
	:mDetails(new ButtonDetails(name, type, w, h, windowDetails, position, scale, rotation))
{
}


Button::~Button()
{
}

void sdlt::Button::addResponder(ButtonResponder * responder)
{
	mResponders.push_back(responder);
}

void Button::handleEvent(SDL_Event * e)
{
	if ((e->type == SDL_MOUSEMOTION) || (e->type == SDL_MOUSEBUTTONDOWN) || (e->type == SDL_MOUSEBUTTONUP))
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool isInside = true;

		if (x < mDetails->getX()) isInside = false; // Left
		if (y < mDetails->getY()) isInside = false; // Up
		if (x > mDetails->getX() + mDetails->getWidth()) isInside = false; // Right
		if (y > mDetails->getY() + mDetails->getHeight()) isInside = false; // Down

		if (isInside)
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				updateState(ButtonState::BS_MOUSE_OVER);
				break;
			case SDL_MOUSEBUTTONDOWN:
				updateState(ButtonState::BS_MOUSE_DOWN);
				break;
			case SDL_MOUSEBUTTONUP:
				updateState(ButtonState::BS_MOUSE_UP);
				break;
			default:
				break;
			}
		}
		else
		{
			updateState(ButtonState::BS_MOUSE_OUT);
		}
	}
}

ButtonDetailsSPtr sdlt::Button::getDetails()
{
	return mDetails;
}

void Button::updateState(ButtonState newState)
{
#ifdef _DEBUG_
	switch (newState)
	{
	case sdlt::ButtonState::BS_MOUSE_OUT:
		std::cout << "BS_MOUSE_OUT" << std::endl;
		break;
	case sdlt::ButtonState::BS_MOUSE_OVER:
		std::cout << "BS_MOUSE_OVER" << std::endl;
		break;
	case sdlt::ButtonState::BS_MOUSE_DOWN:
		std::cout << "BS_MOUSE_DOWN" << std::endl;
		break;
	case sdlt::ButtonState::BS_MOUSE_UP:
		std::cout << "BS_MOUSE_UP" << std::endl;
		break;
	default:
		break;
	}
#endif // _DEBUG_


	if (mDetails->getState() != newState)
	{
		mDetails->setState(newState);
		for (std::list<ButtonResponder*>::iterator it=mResponders.begin(); it != mResponders.end(); ++it)
		{
			ButtonResponder* res = *it;
			(*res)(mDetails);
		}
	}
}
