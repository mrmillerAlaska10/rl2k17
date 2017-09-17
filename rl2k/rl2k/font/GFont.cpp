#include "GFont.h"



GFont::GFont()
{
	defaultFont = TTF_OpenFont("data/fonts/OpenSans-Regular.ttf", 28);
}


GFont::~GFont()
{
}

TTF_Font * GFont::getFont()
{
	return defaultFont;
}
