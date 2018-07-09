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

#include "sdltRenderNode.h"

#include "sdltError.h"

#include <iostream>

using namespace sdlt;

sdlt::RenderNode::RenderNode()
	:mWindowDetails{ new WindowDetails{ nullptr, nullptr } }, 
	mPosition{}
{
}

sdlt::RenderNode::RenderNode(int x, int y, double scaleX, double scaleY, double rotation)
	:mWindowDetails{ new WindowDetails{nullptr, nullptr} }
{
	throw;
}

RenderNode::RenderNode(
	WindowDetailsSPtr windowDetails, Vec2D position, Vec2D scale, double rotation)
	:mWindowDetails{ windowDetails }, mPosition{ position }, mScale{ scale }, mRotation{ rotation }
{
	mScaleCentre = { 0, 0 };
	mCentre = { 0, 0 };
	mParent = nullptr;
}


RenderNode::~RenderNode()
{
	if (mParent != nullptr)
	{
		mParent->removeChild(this);
	}

	for (RenderNode* & node : mChildren)
	{
		// Clear self from children
		node->clearParent();
	}
}


void RenderNode::render(ParentProperties pProperties)
{
	ParentProperties mProp = pProperties;

	mProp.position = applyParentPosition(pProperties);

	mProp.scaleX *= mScale.getX();
	mProp.scaleY *= mScale.getY();
	mProp.rotation += mRotation;

	for (RenderNode* & node : mChildren)
	{
		node->render(mProp);
	}
}

void RenderNode::addChild(RenderNode * newChild)
{
	mChildren.push_back(newChild);
	newChild->setParent(this);
}

void RenderNode::removeChild(RenderNode * child)
{
	mChildren.remove(child);
	child->clearParent();
}

void RenderNode::setPosition(int x, int y)
{
	mPosition.setX(x);
	mPosition.setY(y);
}

void RenderNode::shiftPosition(int dx, int dy)
{
	mPosition.shiftX(dx);
	mPosition.shiftY(dy);
}

void RenderNode::setScaleCentre(int x, int y)
{
	mScaleCentre.x = x;
	mScaleCentre.y = y;
}

void RenderNode::setCentre(int x, int y)
{
	mCentre.x = x;
	mCentre.y = y;
}

void RenderNode::setScale(double x, double y)
{
	mScale.setX(x);
	mScale.setY(y);
}

void RenderNode::shiftScale(double dx, double dy)
{
	mScale.shiftX(dx);
	mScale.shiftY(dy);
}

void RenderNode::setRotation(double rot)
{
	mRotation = rot;
}

int RenderNode::getX() const
{
	return mPosition.getX();
}

int RenderNode::getY() const
{
	return mPosition.getY();
}

// Protected
SDL_Point RenderNode::applyParentPosition(ParentProperties pProperties) const
{
	SDL_Point position;

	//           pos of parent is ture    pos of this in true coords                   Small shift to make sure that this's scale centre is not moved
	//           coords
	position.x = pProperties.position.x + int((mPosition.getX())*pProperties.scaleX) + int((mScaleCentre.x - mScaleCentre.x*mScale.getX() - mCentre.x)*pProperties.scaleX);
	position.y = pProperties.position.y + int((mPosition.getY())*pProperties.scaleY) + int((mScaleCentre.y - mScaleCentre.y*mScale.getY() - mCentre.y)*pProperties.scaleY);

	return position;
}

// ############### //
// Private methods //


void RenderNode::setParent(RenderNode * par)
{
	if (this != par)
	{
		mParent = par;
	}
	else
	{
		throw qdt::node_error("RenderNode::setParent", "Can't be parent of self");
	}
}

void RenderNode::clearParent()
{
	mParent = nullptr;
}
