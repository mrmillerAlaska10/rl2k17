#pragma once
#include "GWidget.h"
using namespace std;

class GButton : 
	public GWidget
{
public:
	GButton();
	GButton(int x, int y);
	GButton(int x, int y, int width, int height);
	~GButton();
	void Init();

	void Render(SDL_Renderer * renderer);

	bool Click();
	std::function<void()> onClick;
protected:
	
};