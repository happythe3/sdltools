#pragma once

#include <string>
#include <map>

#include <SDL.h>

#include "sdltError.h"


class qdtTexture
{
public:
	qdtTexture();
	~qdtTexture();

	void render(SDL_Renderer* renderer, SDL_Rect * drect = NULL);

	// Load texture from disk
	static void load(SDL_Renderer* renderer, std::string path);
	// Gets texture from preloaded set
	static qdtTexture* get(std::string name);
	// Frees texture with name, name
	static void freeTexture(std::string name);
private:
	SDL_Texture* m_texture;

	std::string m_name;

	int mW;
	int mH;



	static std::map<std::string, qdtTexture*> loaded_textures;
};