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

void example1()
{
	// Load SDL
	sdlt::Manager sdlManager{}; 

	// Make a window
	sdlt::Window window{ 
		"Aliens Overrun", // Title
		1000,             // Width
		1000,             // Height
		0 };              // SDL flags

	std::list<std::unique_ptr<sdlt::RenderNode>> renderItems;

	for (size_t i = 0; i < 5; i++)
	{
		renderItems.push_back(
			std::unique_ptr<sdlt::RenderNode>{
			new sdlt::Square(
				window.getWindowDetails(),
				rand() % 900, rand() % 900,
				100,
				sdlt::Colour::random()
			)
		}
		);
		window.addChild(renderItems.back().get());
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
				case SDLK_w:
					renderItems.clear();
					break;
				default:
					renderItems.clear();
					for (size_t i = 0; i < 5; i++)
					{
						renderItems.push_back(
							std::unique_ptr<sdlt::RenderNode>{
							new sdlt::Square(
								window.getWindowDetails(),
								rand() % 900, rand() % 900,
								100,
								sdlt::Colour::random()
							)
						}
						);
						window.addChild(renderItems.back().get());
					}
				}
			}
		}

		window.render();
	}
}