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


enum BarType {
	BarHorizontal,
	BarVertical
};

class qdtProgressBar :
	public sdlt::RenderNode
{
public:
	qdtProgressBar(int x, int y, int w, int h, SDL_Colour empty, SDL_Colour full, BarType type = BarHorizontal);
	~qdtProgressBar();

	void render(SDL_Renderer* renderer, sdlt::ParentProperties pProperties);

	void setPercentage(double newPercentage);

	void updateSize(int w, int h);
private:
	int mW;
	int mH;

	SDL_Colour mEmptyCol;
	SDL_Colour mFullCol;

	BarType mType;

	double mFillPercent;
};