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