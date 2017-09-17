#pragma once
#include "GWidget.h"
#include "GMenuItem.h"


class GMenu :
	public GWidget
{
public:

	GMenu( SDL_Renderer * renderer,int x = 0, int y = 0, int width = 300, int height = 150);
	void Render(SDL_Renderer * renderer);
	void Init();

	template <typename  T>
	void load(vector<T*> collection)
	{
		for (int i = 0; i < items.size(); i++)
		{
			//delete items[i];
		}
		items = vector<GMenuItem*>();
		for (int i = 0; i < collection.size(); i++ )
		{
			string label = collection[i]->name;
			makeItem(label);
			ToggleMenu();
		}
	}
	void OpenMenu();
	void CloseMenu();
	void ToggleMenu();

	void makeItem(string label);
	vector<GMenuItem*> items;
	SDL_Renderer * renderer;

	bool open = true;


	//std::function<void()> onLoad(vector<T*> collection);
};

