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

