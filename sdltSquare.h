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

namespace sdlt
{

	class Square :
		public RenderNode
	{
	public:
		Square(WindowDetailsSPtr window, int x, int y, int size, SDL_Colour colour,
			double scaleX = 1.0, double scaleY = 1.0, double rotation = 0.0);
		~Square();

		void render(ParentProperties pProperties);

	private:
		int mSize;
		SDL_Colour mColour;
	};

}