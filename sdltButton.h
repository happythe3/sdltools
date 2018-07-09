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
#include "sdltRenderNode.h"

#include <iostream>
#include <string>

#include <SDL.h>


class qdtButtonResponder; //Forward decleration

enum ButtonState {
	BS_MOUSE_OUT = 0,
	BS_MOUSE_OVER = 1,
	BS_MOUSE_DOWN = 2,
	BS_MOUSE_UP = 3,
	BS_TOTAL = 4
};

enum ButtonType {
	BT_NORMAL,
	BT_TOGGLE
};

class qdtButton :
	public sdlt::RenderNode
{
public:
	qdtButton(std::string buttonName, ButtonType type, int x, int y, int w, int h, 
		double scaleX = 1.0, double scaleY = 1.0, double rotation = 0.0);
	~qdtButton();

	void setHandler(qdtButtonResponder* responder);
	void setRenderItem(ButtonState state, RenderNode* item);

	void render(SDL_Renderer* renderer, ParentProperties pProperties);
	void handleEvent(SDL_Event * e);

	ButtonState getState() const;

	const std::string mName;



private:
	void setState(ButtonState newState);


	int mW, mH;

	qdtButtonResponder* mResponder;

	ButtonType mType;

	ButtonState mCurrentState;

	RenderNode* mButtonRenderItems[BS_TOTAL];
};





class qdtButtonResponder
{
public:
	qdtButtonResponder();
	~qdtButtonResponder();
	virtual void stateChange(qdtButton* button);
};