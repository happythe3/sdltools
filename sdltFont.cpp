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

#include "sdltFont.h"

using namespace sdlt;


Font::Font(std::string path, int size)
	:mName(path), mSize(size)
{
	mFont = TTF_OpenFont(path.c_str(), size);
	if (mFont == NULL)
	{
		throw f_error(path, TTF_GetError());
	}
}


Font::~Font()
{
	TTF_CloseFont(mFont);
}

std::string Font::name() const
{
	return mName;
}

int Font::size() const
{
	return mSize;
}

TTF_Font * Font::font()
{
	return mFont;
}