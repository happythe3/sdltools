#pragma once
#include "sdltSprite.h"

#include <vector>

class qdtSpriteAnimated :
	public qdtSprite
{
public:
	qdtSpriteAnimated(int x, int y, qdtSpriteSheet* spriteSheet, std::vector<int> spriteID, 
		double scaleX = 1.0, double scaleY = 1.0, double rotation = 0.0);
	~qdtSpriteAnimated();

	void render(SDL_Renderer* renderer, ParentProperties pProperties);
protected:
	std::vector<int> mSpriteIDs;
	mutable int mCurrFrame;
};

