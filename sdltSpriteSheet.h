#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>


class qdtSpriteSheet
{
public:
	qdtSpriteSheet(SDL_Texture* texture, int h, int w, std::string path);
	~qdtSpriteSheet();

	// Gets the numID for a specific strID
	int getSpriteNumID(std::string strID) const;
	// Returns a vector<int> of IDs for given vector<string>
	std::vector<int> getNumIDs(std::vector<std::string> strIDs) const;


	//Returns sprite sheet texture
	SDL_Texture* getSheet() const;
	//Returns clip for specific sprite ID O(1)
	SDL_Rect getClip(int spriteID) const;
	//Returns clip for specific sprite ID O(log(n))
	SDL_Rect getClip(std::string strID) const;





	// ############ //
	// Static stuff //
	// ############ //

	// Loads resource from disk
	static void load(SDL_Renderer* renderer, std::string path);
	// Loads a sprite sheet with given name
	static void loadWithName(
		SDL_Renderer* renderer, 
		std::string path, 
		std::string name);
	// Returns a sprite sheet object that was loaded from 'path'
	static qdtSpriteSheet* get(std::string path);
	// Frees all resources
	static void freeAll();
private:
	// Adds a spriteClip to list and returns sprite ID
	int addSprite(SDL_Rect spriteClip);
	int addSprite(SDL_Rect spriteClip, std::string strID);
	// Sets the string associated with specific numID. Returns true on success
	bool setSpriteStringID(int numID, std::string strID);

	std::string mSheetPath;

	std::map<std::string, int> mStringIDMap;
	std::vector<SDL_Rect> mSpriteClips;

	SDL_Texture* mTexture;

	int mWidth, mHeight;




	// ############ //
	// Static stuff //
	// ############ //
	static std::map<std::string, qdtSpriteSheet*> loaded_sheets;
};
