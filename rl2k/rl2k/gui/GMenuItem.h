#pragma once
#include <string>
#include "GWidget.h"
#include "../font/GMessage.h"
class GMenu;
using namespace std;

class GMenuItem:
	public GWidget
{
public:
	GMenuItem(string label, SDL_Renderer * renderer);
	~GMenuItem(); 
	void Init();
	void Render(SDL_Renderer * renderer);
	string label;


private:
	
	GMessage * text;
	GMenu * Parent;

	SDL_Renderer * rendRef;

	
};

