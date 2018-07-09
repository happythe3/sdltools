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

#include "sdltButtonDetails.h"

using namespace sdlt;

sdlt::ButtonDetails::ButtonDetails(
	std::string name, 
	ButtonType type, 
	int w, int h, 
	WindowDetailsSPtr windowDetails, 
	Vec2D position, 
	Vec2D scale, 
	double rotation)
	:RenderNode(windowDetails, position, scale, rotation), 
	mName(name), mType(type),  mState(ButtonState::BS_MOUSE_OUT),
	mWidth(w), mHeight(h)
{
	for (int i = 0; i < int(ButtonState::BS_TOTAL); i++)
	{
		mButtonRenderItems[i] = NULL;
	}
}

sdlt::ButtonDetails::~ButtonDetails()
{
}

void sdlt::ButtonDetails::render(ParentProperties pProperties)
{
	ParentProperties mProp = pProperties;

	mProp.position = applyParentPosition(pProperties);

	mProp.scaleX *= mScale.getX();
	mProp.scaleY *= mScale.getY();
	mProp.rotation += mRotation;

	if (mButtonRenderItems[int(mState)] != NULL)
	{
		mButtonRenderItems[int(mState)]->render(mProp);
	}
	else if (mButtonRenderItems[int(ButtonState::BS_MOUSE_OUT)] != NULL)
	{
		mButtonRenderItems[int(ButtonState::BS_MOUSE_OUT)]->render(mProp);
	}
	else
	{
		std::cout << "sdlt::ButtonDetails::render || button: '" << mName << "' has no default render item." << std::endl;
	}
}

void sdlt::ButtonDetails::setRenderItem(ButtonState state, RenderNode * item)
{
	mButtonRenderItems[int(state)] = item;
}

void sdlt::ButtonDetails::setAllRenderItems(RenderNode * items[int(ButtonState::BS_TOTAL)])
{
	for (size_t i = 0; i < int(ButtonState::BS_TOTAL); i++)
	{
		mButtonRenderItems[i] = items[i];
	}
}

ButtonState sdlt::ButtonDetails::getState() const
{
	return mState;
}

int sdlt::ButtonDetails::getWidth() const
{
	return mWidth;
}

int sdlt::ButtonDetails::getHeight() const
{
	return mHeight;
}

void sdlt::ButtonDetails::setState(ButtonState newState)
{
	mState = newState;
}
