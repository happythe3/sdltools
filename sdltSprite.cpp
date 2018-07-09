#include "sdltSprite.h"



qdtSprite::qdtSprite(int x, int y, const qdtSpriteSheet* spriteSheet, int spriteID, 
	double scaleX, double scaleY, double rotation)
	:RenderNode(x, y, scaleX, scaleY, rotation)
{
	mSpriteSheet = spriteSheet;
	mSpriteID = spriteID;
}

qdtSprite::~qdtSprite()
{
}

void qdtSprite::render(SDL_Renderer * renderer, ParentProperties pProperties)
{
	SDL_Rect renderClip = mSpriteSheet->getClip(mSpriteID);

	SDL_Point pos = applyParentPosition(pProperties);

	SDL_Rect renderRect = {
		pos.x,
		pos.y,
		int(renderClip.w*pProperties.scaleX * mScale.getX()),
		int(renderClip.h*pProperties.scaleY * mScale.getY())
	};

	SDL_RenderCopyEx(
		renderer, 
		mSpriteSheet->getSheet(), 
		&renderClip, &renderRect, 
		pProperties.rotation + mRotation, 
		NULL, 
		SDL_FLIP_NONE
	);

	// Done at end so that it is drawn over other items
	RenderNode::render(renderer, pProperties);
}