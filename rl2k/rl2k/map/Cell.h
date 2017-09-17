#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include "TileSet.h"
class Actor;
using namespace std;

enum cellType
{
	CELL_FLOOR = 19,
	CELL_FLOOR_TUNNEL,
	CELL_WALL =22,
	CELL_BORDER =23,
	CELL_DOOR =1,
	CELL_BROKEN_DOOR = 2,
	CELL_UP =75,
	CELL_DOWN = 42
};


class Cell
{
public:
	Cell();
	~Cell();
	int x, y;
	void setTile(cellType t);
	void Render(SDL_Renderer * Render, TileSet * set, int x, int y);
	cellType getType();
	bool IsWalkable(cellType type, bool checkCollision = false);
	
	Actor * getAttachedActor();
	bool AttachActor(Actor * actor);
	void RemoveActor();

	Actor * getAttachedItem();
	bool AttachItem(Actor * actor);
	void RemoveItem();
	
	void ConsolePrint();
private:
	//includes monsters npcs and player. excludes items
	Actor * attachedActor =nullptr;
	//items on the ground. a monster and item can occupy the same space.
	//TO DO: Have multiple items on a tile form stacks
	Actor * attachedItem = nullptr;
	cellType cellClassification = cellType::CELL_FLOOR;
	
};

