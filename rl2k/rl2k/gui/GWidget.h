#pragma once
#include "../engine/graphics/Texture.h"
#include <SDL.h>
#include <vector>
#include <functional>
class GBase;

using namespace std;
//Base gui item
class GWidget
{
public:

	GWidget();
	~GWidget();
	virtual void Init() = 0;

	//handles relevant input. By default do nothing
	void ProcessInput(SDL_Event &e);
	//this calls the render function for all children
	void Draw(SDL_Renderer * renderer);

	void Refresh();

	//calls the on refresh function. Must be invoked manually
	

	void resize(int w, int h);
	void setX(int x);
	void setY(int y);

	void addX(int add);
	void addY(int add);
	void setParent(GWidget * widget);
	void setColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A);
	
	int getX();
	int getY();
	int getWidth();
	int getHeight(); 
	void setVisibility(bool visible);
	void toggleVisibility();
protected:
	//every widget should call this in the constructor to initialize
	void CreateWidget(GBase * container);
	void WidgetInit();
	
	//overridable functions
	//handles the input for the component itself
	virtual void Input(SDL_Event &e);
	//This draws the component itself
	virtual void Render(SDL_Renderer * renderer) = 0;
	
	//ownership tree
	GWidget * parent;
	vector<GWidget*> children;
	//this is the root gui item. All gui items must reference it.
	GBase * container;
	//properies
	//==============
	//window
	int x, y, width, height;
	//color
	int red = 200;
	int green = 200;
	int blue = 200;
	int alpha = 255;
	Texture * Background;
	//focus
	GWidget * FocusedChild;

	void DetectEvents(SDL_Event &e);

	
	
public:

	bool WasClicked();
	virtual bool Click();
	std::function<void()> onRefresh;
	bool hidden = false;

};

