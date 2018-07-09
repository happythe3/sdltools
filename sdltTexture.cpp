#include "sdltTexture.h"

#include <iostream>

#include <SDL_image.h>


std::map<std::string, qdtTexture*> qdtTexture::loaded_textures = {};

qdtTexture::qdtTexture()
{

}

qdtTexture::~qdtTexture()
{
	std::cout << "Destroying texture - " << m_name << std::endl;
	
	SDL_DestroyTexture(m_texture);
}

void qdtTexture::render(SDL_Renderer * renderer, SDL_Rect * drect)
{
	if (SDL_RenderCopy(renderer, m_texture, NULL, drect) == -1)
	{
		throw qdt::render_error("qdtTexture", SDL_GetError());
	}
}




void qdtTexture::load(SDL_Renderer * renderer, std::string path)
{
	if (loaded_textures.count(path) != 0)
	{
		throw qdt::already_loaded{ "qdtTexture", path, "resource already loaded" };
	}

	std::cout << "Loading texture - " << path << std::endl;

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		throw qdt::NULL_surface{ "qdtTexture", path, IMG_GetError(), };
	}

	qdtTexture* newTexture = new qdtTexture{};

	newTexture->m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (newTexture->m_texture == NULL)
	{
		throw qdt::NULL_texture{ "qdtTexture", path, SDL_GetError() };
	}

	newTexture->mH = surface->h;
	newTexture->mW = surface->w;
	newTexture->m_name = path;

	SDL_FreeSurface(surface);

	loaded_textures.insert(std::pair<std::string, qdtTexture*>(path, newTexture));
}

qdtTexture* qdtTexture::get(std::string name)
{
	if (loaded_textures.count(name) == 0)
	{
		throw qdt::not_loaded("qdtTexture", name, "resource not loaded");
	}
	return loaded_textures.at(name);
}

void qdtTexture::freeTexture(std::string name)
{
	delete loaded_textures.at(name);

	loaded_textures.erase(name);
}