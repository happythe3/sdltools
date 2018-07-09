#include "sdltSpriteAnimated.h"



qdtSpriteAnimated::qdtSpriteAnimated(int x, int y, qdtSpriteSheet * spriteSheet, 
	std::vector<int> spriteIDs, double scaleX, double scaleY, double rotation)
	:qdtSprite(x, y, spriteSheet, -1, scaleX, scaleY, rotation)
{
	mSpriteIDs = spriteIDs;
	mCurrFrame = 0;
}


qdtSpriteAnimated::~qdtSpriteAnimated()
{
}


void qdtSpriteAnimated::render(SDL_Renderer * renderer, ParentProperties pProperties)
{
	SDL_Rect renderClip = mSpriteSheet->getClip(mSpriteIDs[mCurrFrame]);
	mCurrFrame++;
	if (mCurrFrame == mSpriteIDs.size())
	{
		mCurrFrame = 0;
	}

	SDL_Point pos = applyParentPosition(pProperties);

	SDL_Rect renderRect = {
		pos.x,
		pos.y,
		int(renderClip.w*pProperties.scaleX * mScale.getX()),
		int(renderClip.h*pProperties.scaleY * mScale.getY())
	};

	SDL_RenderCopy(renderer, mSpriteSheet->getSheet(), &renderClip, &renderRect);

	// Done at end so that it is drawn over other items
	RenderNode::render(renderer, pProperties);
}