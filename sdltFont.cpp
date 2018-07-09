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



qdtFont::qdtFont(std::string path, int size)
	:m_name(path), m_size(size)
{
	m_font = TTF_OpenFont(path.c_str(), size);
	if (m_font == NULL)
	{
		throw qdt::f_error(path, TTF_GetError());
	}

}


qdtFont::~qdtFont()
{
	TTF_CloseFont(m_font);
}

std::string qdtFont::name() const
{
	return m_name;
}

int qdtFont::size() const
{
	return m_size;
}

TTF_Font * qdtFont::font()
{
	return m_font;
}