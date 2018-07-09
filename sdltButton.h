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