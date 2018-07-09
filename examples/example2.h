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

#include "../sdltSDLManager.h"
#include "../sdltWindow.h"
#include "../sdltColours.h"
#include "../sdltSquare.h"
#include "../sdltButton.h"

using namespace sdlt;

void example2()
{
	// Load SDL
	sdlt::Manager sdlManager{};

	// Make a window
	sdlt::Window window{
		"Example2",       // Title
		1000,             // Width
		1000,             // Height
		0 };              // SDL flags

	std::list<std::shared_ptr<sdlt::RenderNode>> renderItems;
	std::vector<std::shared_ptr<Button>> buttons;

	{
		buttons.push_back(
			std::shared_ptr<Button>{
			new Button(
				"Button 1",
				ButtonType::BT_NORMAL,
				100, 100,
				window.getWindowDetails(),
				Vec2D(200, 200))
		});

		ButtonDetailsSPtr bd = buttons[0]->getDetails();

		bd->setRenderItem(ButtonState::BS_MOUSE_OUT,
			new sdlt::Square(
				window.getWindowDetails(),
				0, 0,
				100,
				sdlt::Colour::green()
			)
		);

		bd->setRenderItem(ButtonState::BS_MOUSE_OVER,
			new sdlt::Square(
				window.getWindowDetails(),
				0, 0,
				100,
				sdlt::Colour::orange()
			)
		);

		bd->setRenderItem(ButtonState::BS_MOUSE_DOWN,
			new sdlt::Square(
				window.getWindowDetails(),
				0, 0,
				100,
				sdlt::Colour::red()
			)
		);

		window.addChild(bd.get());

	}

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_q:
					quit = true;
					break;
				default:
					break;
				}
			}

			for (size_t i = 0; i < buttons.size(); i++)
			{
				buttons[i]->handleEvent(&e);
			}
		}

		window.render();
	}
}