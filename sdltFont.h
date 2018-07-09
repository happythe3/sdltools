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

#include <string>
#include <map>

#include <SDL_ttf.h>

namespace qdt {
	struct f_error {
		f_error(std::string n, const char* e) {
			name = n;
			error = e;
		}
		std::string name;
		const char* error;
	};
}

class qdtFont
{
public:
	qdtFont(std::string path, int size);
	~qdtFont();


	// Returns the name of the font
	std::string name() const;
	// Returns the size of the font
	int size() const;
	// Returns a pointer to the font
	TTF_Font* font();
private:
	TTF_Font* m_font;
	int m_size;
	std::string m_name;
};

