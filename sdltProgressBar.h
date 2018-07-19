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
	class ProgressBar :
		public sdlt::RenderNode
	{
	public:
		ProgressBar(WindowDetailsSPtr windowDetails);
		ProgressBar(
			WindowDetailsSPtr windowDetails,
			Vec2D position,
			Vec2D size,
			SDL_Colour empty,
			SDL_Colour full,
			Vec2D scale = Vec2D{ 1, 1 },
			double rotation = 0.0
		);
		~ProgressBar();

		void render(ParentProperties pProperties);

		void setPercentage(double newPercentage);

		void updateSize(int w, int h);
		void updateSize(Vec2D size);
	private:
		Vec2D mSize;

		SDL_Colour mEmptyCol;
		SDL_Colour mFullCol;

		double mFillPercent;
	};
}
