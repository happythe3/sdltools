#pragma once

#include <list>

#include <SDL.h>

#include "sdltWindowDetails.h"
#include "sdltVec2D.h"

struct ParentProperties
{
	SDL_Point position;
	double scaleX;
	double scaleY;
	double rotation;
};


namespace sdlt
{
	class RenderNode
	{
	public:
		RenderNode();
		RenderNode(int x, int y, double scaleX = 1.0, double scaleY = 1.0, double rotation = 0.0);
		RenderNode(
			WindowDetailsSPtr windowDetails,
			Vec2D position,
			Vec2D scale = Vec2D{ 1, 1 },
			double rotation = 0.0
		);
		virtual ~RenderNode();

		virtual void render(SDL_Renderer* renderer, ParentProperties pProperties) { throw; }
		virtual void render(ParentProperties pProperties);

		void addChild(RenderNode * newChild);
		void removeChild(RenderNode * child);

		void setPosition(int x, int y);
		void shiftPosition(int dx, int dy);
		void setScaleCentre(int x, int y);
		void setCentre(int x, int y);
		void setScale(double x, double y);
		void shiftScale(double dx, double dy);
		void setRotation(double rot);

		int getX() const;
		int getY() const;
	protected:
		void setParent(RenderNode* par);
		void clearParent();

		WindowDetailsSPtr mWindowDetails;

		// Returns an SDL_Point of this objects position in screen coords
		SDL_Point applyParentPosition(ParentProperties pProperties) const;

		std::list<RenderNode*> mChildren;

		Vec2D mPosition;
		Vec2D mScale;
		double mRotation;
		SDL_Point mScaleCentre;
		SDL_Point mCentre;

		RenderNode* mParent;
	};

}