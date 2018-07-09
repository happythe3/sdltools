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