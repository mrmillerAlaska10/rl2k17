#include "Cell.h"


Cell::Cell()
{
}


Cell::~Cell()
{
}

void Cell::setTile(cellType t)
{
	this->cellClassification = t;
}

void Cell::Render(SDL_Renderer * Render, TileSet * set, int x, int y)
{
	
	set->Render(Render, this->cellClassification, x, y);
}

cellType Cell::getType()
{
	return this->cellClassification;
}

bool Cell::IsWalkable(cellType type, bool checkCollision)
{
	bool walkable = false;
	switch (type)
	{
	case CELL_FLOOR:		
	case CELL_FLOOR_TUNNEL:
	case CELL_BROKEN_DOOR:
	case CELL_DOOR:
	case CELL_UP:
	case CELL_DOWN:
		walkable = true;
	break;
	
	}
	if (checkCollision)
	{
		if (getAttachedActor() != nullptr)
		{
			walkable = false;
		}
	}

	
	return walkable;
}

Actor * Cell::getAttachedActor()
{
	return attachedActor;
}

bool Cell::AttachActor(Actor * actor)
{
	if (attachedActor != nullptr)
	{
		return false;
	}

	attachedActor = actor;
	{return true; }
}

void Cell::RemoveActor()
{
	attachedActor = nullptr;
}

Actor * Cell::getAttachedItem()
{
	return attachedItem;
}

bool Cell::AttachItem(Actor * actor)
{
	if (attachedItem != nullptr)
	{
		return false;
	}

	attachedItem = actor;
	{return true; }
}

void Cell::RemoveItem()
{
	attachedItem = nullptr;
}


void Cell::ConsolePrint()
{
	string symbol = ".";
	switch (cellClassification)
	{
	case CELL_FLOOR:
		break;
	case CELL_FLOOR_TUNNEL:
		break;
	case CELL_WALL:
		symbol = "#";
		break;
	case CELL_BORDER:
		symbol = "B";
		break;
	case CELL_DOOR:
		symbol = ",";
		break;
	case CELL_UP:
		symbol = ">";
		break;
	case CELL_DOWN:
		symbol = "<";
		break;
	case CELL_BROKEN_DOOR:
		break;
	default:
		break;
	}
	cout << symbol;
}
