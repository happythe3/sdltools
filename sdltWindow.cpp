#include "sdltWindow.h"


using namespace std;
using namespace sdlt;


Window::Window(string windowName, int width, int height, Uint32 flags)
	:mColour{ 0xFF, 0xFF, 0xFF, 0xFF }
{
	// Create window and renderer
	SDL_Window * window;
	SDL_Renderer * renderer;
	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, flags);

	if (window == NULL)
	{
		cout << "qdtWindow::qdtWindow || Winodw creation failed" << endl;
		cout << "SDL_Error: " << SDL_GetError() << endl;
	}
	else
	{
		SDL_GetWindowSize(window, &mWidth, &mHeight);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL)
		{
			cout << "qdtWindow::qdtWindow || Renderer creation failed" << endl;
			cout << "SDL_Error: " << SDL_GetError() << endl;
		}
		else
		{
			// Successfully created everything
			mWindowDetails = WindowDetailsSPtr{ new WindowDetails{ window, renderer } };
		}
	}

	SDL_SetRenderDrawColor(mWindowDetails->rendererPtr,
		mColour.r, mColour.g, mColour.b, mColour.a);

	mRenderNode = std::unique_ptr<RenderNode>{ new RenderNode{ mWindowDetails, Position2D{0, 0}} };
}


Window::~Window()
{
	// If this is last object, mWindowDetails wil be destoryed
}

void Window::setBackgroundColour(SDL_Colour c)
{
	mColour = c;
}


SDL_Renderer * Window::getRenderer()
{
	return mWindowDetails->rendererPtr;
}

int Window::getWidth()
{
	return mWidth;
}

int Window::getHeight()
{
	return mHeight;
}

WindowDetailsSPtr sdlt::Window::getWindowDetails()
{
	return mWindowDetails;
}


void Window::render()
{
	SDL_SetRenderDrawColor(mWindowDetails->rendererPtr, 
		mColour.r, 
		mColour.g, 
		mColour.b, 
		mColour.a);

	SDL_RenderClear(mWindowDetails->rendererPtr);


	ParentProperties mProp;
	mProp.position.x = 0;
	mProp.position.y = 0;
	mProp.scaleX = 1.0;
	mProp.scaleY = 1.0;
	mProp.rotation = 0.0;

	mRenderNode->render(mProp);

	SDL_RenderPresent(mWindowDetails->rendererPtr);
}

void Window::addChild(RenderNode * newChild)
{
	mRenderNode->addChild(newChild);
}