#include "sdltSpriteSheet.h"

#include <fstream> // std::ofstream
#include <regex>

#include "../tinyxml2/tinyxml2.h"

#include "sdltError.h"

using namespace std;
using namespace qdt;
using namespace tinyxml2;

std::map<std::string, qdtSpriteSheet*> qdtSpriteSheet::loaded_sheets = {};

qdtSpriteSheet::qdtSpriteSheet(SDL_Texture * texture, int h, int w, std::string path)
	:mSpriteClips{}
{
	mTexture = texture;
	mHeight = h;
	mWidth = w;
	mSheetPath = path;
}

qdtSpriteSheet::~qdtSpriteSheet()
{
	std::cout << "Destorying spritesheet - " << mSheetPath << std::endl;

	SDL_DestroyTexture(mTexture);
}

int qdtSpriteSheet::addSprite(SDL_Rect spriteClip)
{
	mSpriteClips.push_back(spriteClip);

	return int(mSpriteClips.size() - 1);
}

int qdtSpriteSheet::addSprite(SDL_Rect spriteClip, std::string strID)
{
	int numID = addSprite(spriteClip);

	if (!setSpriteStringID(numID, strID)) {
		std::cout << "qdtSpriteSheet::addSprite | strID " << strID << " already in use." << std::endl;
	}

	return numID;
}

bool qdtSpriteSheet::setSpriteStringID(int numID, std::string strID)
{
	std::pair<std::map<std::string, int>::iterator, bool> ret;
	ret = mStringIDMap.insert(std::pair<std::string, int>(strID, numID));
	if (ret.second == false) {
		std::cout << "qdtSpriteSheet::setSpriteStringID | strID " << strID << " already in use." << std::endl;
		return false;
	}
	return true;
}

int qdtSpriteSheet::getSpriteNumID(std::string strID) const
{
	return mStringIDMap.at(strID);
}

std::vector<int> qdtSpriteSheet::getNumIDs(std::vector<std::string> strIDs) const
{
	vector<int> intIDs{};
	for (string & ID : strIDs)
	{
		intIDs.push_back(getSpriteNumID(ID));
	}
	return intIDs;
}

SDL_Texture * qdtSpriteSheet::getSheet() const
{
	return mTexture;
}

SDL_Rect qdtSpriteSheet::getClip(int spriteID) const
{
	return mSpriteClips.at(spriteID);
}

SDL_Rect qdtSpriteSheet::getClip(std::string strID) const
{
	return getClip(getSpriteNumID(strID));
}



// ############ //
// Static stuff //
// ############ //

void qdtSpriteSheet::load(SDL_Renderer* renderer, std::string path)
{
	loadWithName(renderer, path, path);
}

void qdtSpriteSheet::loadWithName(
	SDL_Renderer * renderer, 
	std::string path, 
	std::string name)
{
	if (loaded_sheets.count(name) != 0)
	{
		throw qdt::already_loaded{ "qdtSpriteSheet", path, "name - " + name + " - already in use" };
	}

	XMLDocument doc{};
	string xml_path = path + ".xml";
	XMLError err = doc.LoadFile(xml_path.c_str());
	if (err != XML_SUCCESS)
	{
		throw resource_error{
			"qdtSrpiteSheet::loadWithName",
			path + ".xml",
			"Unable to open file" };
	}

	SDL_Texture* texture;

	std::cout << "Loading sprite sheet - " << path;
	if (path.compare(name) != 0) { std::cout << " as " << name;}
	std::cout << std::endl;

	string img_path = path + ".png";
	SDL_Surface* surface = IMG_Load(img_path.c_str());
	if (surface == NULL)
	{
		throw qdt::NULL_surface{ "qdtSpriteSheet", path, IMG_GetError() };
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
		{
			throw qdt::NULL_texture{ "qdtSpriteSheet", path, SDL_GetError() };

		}
	}

	qdtSpriteSheet* spriteSheet = new qdtSpriteSheet{ texture, surface->h, surface->w, path };
	qdtSpriteSheet::loaded_sheets.insert(std::pair<std::string, qdtSpriteSheet*>(name, spriteSheet));

	SDL_FreeSurface(surface);


	// Doc should be loaded
	XMLElement* spritesheet_details = nullptr;
	spritesheet_details = doc.FirstChildElement("spritesheet");

	if (spritesheet_details != nullptr)
	{
		XMLElement* sprite = nullptr;
		sprite = spritesheet_details->FirstChildElement("sprite");

		while (sprite != nullptr)
		{
			// Process sprite
			spriteSheet->addSprite(
				SDL_Rect{
					atoi(sprite->FirstChildElement("x")->FirstChild()->ToText()->Value()),
					atoi(sprite->FirstChildElement("y")->FirstChild()->ToText()->Value()),
					atoi(sprite->FirstChildElement("w")->FirstChild()->ToText()->Value()),
					atoi(sprite->FirstChildElement("h")->FirstChild()->ToText()->Value()) 
				},
				string(sprite->FirstChildElement("name")->FirstChild()->ToText()->Value())
			);
			// Get next sprite
			spritesheet_details->DeleteChild(sprite);
			sprite = nullptr;
			sprite = spritesheet_details->FirstChildElement("sprite");
		}
	}
}

qdtSpriteSheet* qdtSpriteSheet::get(std::string path)
{
	if (loaded_sheets.count(path) == 0) {
		throw qdt::not_loaded{ "qdtSpriteSheet", path, "spriteSheet not loaded" };
	}
	return loaded_sheets.at(path);
}

void qdtSpriteSheet::freeAll()
{
	for (auto& p : loaded_sheets)
	{
		delete p.second;
	}

	loaded_sheets.clear();
}