#include "GMenuItem.h"







GMenuItem::GMenuItem(string label, SDL_Renderer * renderer)
{
	this->label = label;
	this->rendRef = renderer;
}

GMenuItem::~GMenuItem()
{
}

void GMenuItem::Init()
{
	WidgetInit();
	text = new GMessage(rendRef);
	text->Write(label);

	//this->setColor(255, 0, 0, 255);
}

void GMenuItem::Render(SDL_Renderer * renderer)
{
	Background->render(this->x, this->y, renderer);
	if (label != "")
	{
		this->text->Draw(this->x,this->y);
	}
}
