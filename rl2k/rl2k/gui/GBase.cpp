#include "GBase.h"



GBase::GBase()
{
}


GBase::~GBase()
{
}

void GBase::addRoot(GWidget * widget)
{
	roots.push_back(widget);
}

void GBase::ProcessInput(SDL_Event & e)
{
	for (int i = 0; i < roots.size(); i++)
	{
		roots[i]->ProcessInput(e);
	}
}

void GBase::Draw(SDL_Renderer * renderer)
{
	for (int i = 0; i < roots.size(); i++)
	{
		roots[i]->Draw(renderer);
	}
}

void GBase::Refresh()
{
	for (int i = 0; i < roots.size(); i++)
	{
		roots[i]->Refresh();
	}
}
