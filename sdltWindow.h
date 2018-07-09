#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <SDL.h>

#include "sdltRenderNode.h"
#include "sdltWindowDetails.h"


namespace sdlt // SDL Tools
{
	class Window
	{
	public:
		Window(std::string windowName, int width, int height, Uint32 flags);
		~Window();

		void setBackgroundColour(SDL_Colour colour);


		// Getters //

		SDL_Renderer* getRenderer();
		int getWidth();
		int getHeight();
		WindowDetailsSPtr getWindowDetails();

		// Getters //


		void render();

		void addChild(RenderNode* newChild);
	private:
		WindowDetailsSPtr mWindowDetails;
		std::unique_ptr<RenderNode> mRenderNode;

		SDL_Colour mColour;

		int mWidth, mHeight;

	};
}