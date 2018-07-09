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

#include "sdltRenderNode.h"

namespace sdlt
{
	enum class ButtonState {
		BS_MOUSE_OUT = 0,
		BS_MOUSE_OVER = 1,
		BS_MOUSE_DOWN = 2,
		BS_MOUSE_UP = 3,
		BS_TOTAL = 4
	};

	enum class ButtonType {
		BT_NORMAL,
		BT_TOGGLE
	};

	class ButtonDetails :
		public RenderNode
	{
	public:
		ButtonDetails(
			std::string name,
			ButtonType type,
			int w, int h,
			WindowDetailsSPtr windowDetails,
			Vec2D position,
			Vec2D scale = Vec2D{ 1, 1 },
			double rotation = 0.0);

		~ButtonDetails();

		virtual void render(ParentProperties pProperties);

		void setRenderItem(ButtonState state, RenderNode* item);
		void setAllRenderItems(RenderNode* item[int(ButtonState::BS_TOTAL)]);

		ButtonState getState() const;
		int getWidth() const;
		int getHeight() const;

		const std::string mName;

		void setState(ButtonState newState);

	private:
		ButtonType mType;
		ButtonState mState;

		int mWidth;
		int mHeight;

		// Stores renderNodes for each button state
		RenderNode* mButtonRenderItems[int(ButtonState::BS_TOTAL)];
	};

	using ButtonDetailsSPtr = std::shared_ptr<ButtonDetails>;
}
