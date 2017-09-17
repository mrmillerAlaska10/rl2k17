#include "GMenu.h"


GMenu::GMenu(SDL_Renderer * renderer,int x, int y, int w, int h)
{
	this->renderer = renderer;
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	Init();
}

void GMenu::Render(SDL_Renderer * renderer)
{
	Background->render(this->x, this->y, renderer);
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Render(renderer);
	}
}

void GMenu::Init()
{
	WidgetInit();
}



void GMenu::OpenMenu()
{
}


void GMenu::CloseMenu()
{
}

void GMenu::ToggleMenu()
{
}

void GMenu::makeItem(string label)
{
	
	GMenuItem *itm = new GMenuItem(label, renderer);
	itm->setX(0);
	itm->setY(items.size() * 40);
	itm->resize(300, 40);
	itm->label = label;
	itm->Init();
	items.push_back(itm);
}
