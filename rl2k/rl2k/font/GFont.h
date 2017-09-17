#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
//class representing a collection of glyphs that can be written out into GMessages.

class GFont
{
public:
	GFont();
	~GFont();
	TTF_Font * getFont();
private:
	TTF_Font * defaultFont = 0;
};

