#pragma once
#include "Cell.h"
#include <SDL.h>
#include "TileSet.h"
class Map
{
public:
	Map();
	~Map();

	void ConstructBlank(int width, int height);	
	Cell * GetTile(int x, int y);

	Cell * GetTile(int x, int y, int direction, int distance);
	
	void Console_Camera_Print(int x, int y, int w, int h, bool center = false);	
	void DrawCamera(SDL_Renderer * Renderer, TileSet * set, int x, int y, int w, int h, bool center = false);
	void consolePrint();
	int stairX = -1;
	int stairY = -1;
private:
	int width;
	int height;
	Cell ** Tiles;

	void makeBorders();
	bool GenerateMap();
	SDL_Rect MakeRoom(int x = 1, int y = 1, int width = 5, int height = 5);
	void DigRoom(int x, int y, int w, int h);

	//starting position
	




};

