#pragma once
#include "GWidget.h"
#include <vector>

using namespace std;
class Actor;
class GBase
{
public:
	GBase();
	~GBase();

	void addRoot(GWidget * widget);

	void ProcessInput(SDL_Event &e);
	void Draw(SDL_Renderer * renderer);
	void Refresh();
private:
	GWidget * focused = nullptr;
	vector<GWidget*> roots;
};

