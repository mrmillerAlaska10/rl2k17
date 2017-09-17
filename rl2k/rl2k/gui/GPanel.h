#pragma once


//plain platform to have other containers
#include "GWidget.h"
class GPanel :
	public GWidget
{
public:
	GPanel();
	~GPanel(); 
	void Init();
protected:
	
	
	//This draws the component itself
	void Render(SDL_Renderer * renderer);
};

