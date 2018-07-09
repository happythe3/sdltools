#pragma once
#include "sdltRenderNode.h"
#include "sdltSpriteSheet.h"

using namespace sdlt;

class qdtSprite :
	public RenderNode
{
public:
	qdtSprite(int x, int y, const qdtSpriteSheet* spriteSheet, 
		int spriteID, double scaleX = 1.0, double scaleY = 1.0, double rotation = 0.0);
	virtual ~qdtSprite();

	virtual void render(SDL_Renderer* renderer, ParentProperties pProperties);
protected:
	const qdtSpriteSheet* mSpriteSheet;
	int mSpriteID;
};

