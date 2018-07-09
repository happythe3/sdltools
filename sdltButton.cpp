#include "sdltButton.h"

using namespace sdlt;


qdtButton::qdtButton(std::string buttonName, ButtonType type, int x, int y, int w, int h,
	double scaleX, double scaleY, double rotation)
	:RenderNode(x, y, scaleX, scaleY, rotation), mName(buttonName)
{
	mType = type;
	mW = w;
	mH = h;

	mResponder = NULL;
	mCurrentState = BS_MOUSE_OUT;

	for (int i = 0; i < BS_TOTAL; i++)
	{
		mButtonRenderItems[i] = NULL;
	}
}


qdtButton::~qdtButton()
{
}


void qdtButton::setHandler(qdtButtonResponder * responder)
{
	mResponder = responder;
}

void qdtButton::setRenderItem(ButtonState state, RenderNode * item)
{
	mButtonRenderItems[state] = item;
}


void qdtButton::render(SDL_Renderer * renderer, ParentProperties pProperties)
{
	ParentProperties mProp = pProperties;

	mProp.position = applyParentPosition(pProperties);

	mProp.scaleX *= mScale.getX();
	mProp.scaleY *= mScale.getY();
	mProp.rotation += mRotation;

	if (mButtonRenderItems[mCurrentState] != NULL)
	{
		mButtonRenderItems[mCurrentState]->render(renderer, mProp);
	}
	else if (mButtonRenderItems[BS_MOUSE_OUT] != NULL)
	{
		mButtonRenderItems[BS_MOUSE_OUT]->render(renderer, mProp);
	}
	else
	{
		std::cout << "qdtButton::render || button: '" << mName << "' has no default render item." << std::endl;
	}
}

void qdtButton::handleEvent(SDL_Event * e)
{
	if (((e->type == SDL_MOUSEMOTION) | e->type == SDL_MOUSEBUTTONDOWN) | e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool isInside = true;

		if (x < mPosition.getX()) isInside = false; // Left
		if (y < mPosition.getY()) isInside = false; // Up
		if (x > mPosition.getX() + mW) isInside = false; // Right
		if (y > mPosition.getY() + mH) isInside = false; // Down

		if (isInside)
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				setState(BS_MOUSE_OVER);
				break;
			case SDL_MOUSEBUTTONDOWN:
				setState(BS_MOUSE_DOWN);
				break;
			case SDL_MOUSEBUTTONUP:
				setState(BS_MOUSE_UP);
				break;
			default:
				break;
			}
		}
		else
		{
			setState(BS_MOUSE_OUT);
		}
	}
}

ButtonState qdtButton::getState() const
{
	return mCurrentState;
}





/* ---- Private ---- */
void qdtButton::setState(ButtonState newState)
{
	if (mCurrentState != newState)
	{
		mCurrentState = newState;
		if (mResponder != NULL)
		{
			mResponder->stateChange(this);
		}
	}
}



/* ---- qdtButtonResponder ---- */
qdtButtonResponder::qdtButtonResponder()
{
}


qdtButtonResponder::~qdtButtonResponder()
{
}


void qdtButtonResponder::stateChange(qdtButton* button)
{
	std::cout << "qdtButtonResponder::stateChange | virtual function running in response to" << std::endl;
	std::cout << button->mName << " chaning to state " << button->getState() << std::endl;
}
