#include "GButton.h"


GButton::GButton()
{
	Init();
}

GButton::GButton(int x, int y)
{
	this->x = x;
	this->y = y;
	Init();
}
GButton::GButton(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	Init();
	
	
}
GButton::~GButton()
{
}

void GButton::Init()
{
	WidgetInit();
	
}
void GButton::Render(SDL_Renderer * renderer)
{
	Background->render(this->x, this->y, renderer);
}

bool GButton::Click()
{
	if (onClick != 0)
	{
		onClick();
		
		return true;
	}
	return false;
}

