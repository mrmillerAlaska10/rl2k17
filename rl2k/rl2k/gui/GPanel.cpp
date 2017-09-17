#include "GPanel.h"



GPanel::GPanel()
{
	
}


GPanel::~GPanel()
{
}

void GPanel::Init()
{
	WidgetInit();
	
	
}

void GPanel::Render(SDL_Renderer * renderer)
{
	Background->render(this->x, this->y, renderer);
}
