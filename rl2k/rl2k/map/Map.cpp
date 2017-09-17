#include "Map.h"
#include <iostream>
#include "../util/Random.h"
#include "gen\Dungeon.h"
using namespace std;

int cellformula(int x, int y, int width, int height)
{
	return height * y + x;
}

Map::Map()
{
}


Map::~Map()
{
}

void Map::ConstructBlank(int width, int height)
{
	this->width = width;
	this->height = height;
	Tiles = new Cell*[width*height];
	
	for (int i = 0; i < width*height; i++)
	{
		Tiles[i] = new Cell();
		Tiles[i]->setTile(cellType::CELL_WALL);
	}
	//ineffecient, but whatever to avoid the math
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			GetTile(x, y)->x = x;
			GetTile(x, y)->y = y;
		}
	}

	makeBorders();
	GenerateMap();
	
}

Cell * Map::GetTile(int x, int y)
{
	if (x < 0 || y < 0)
		return NULL;
	if (cellformula(x, y, width, height) >= (width*height))
	{
		return NULL;
	}
	return Tiles[cellformula(x,y,width,height)];
}

Cell * Map::GetTile(int x, int y, int direction, int distance)
{
	switch (direction)
	{
	//north
	case 7:
		x = x - distance;
		y = y - distance;
		break;
	case 8:		
		y = y - distance;
		break;
	case 9:
		x = x + distance;
		y = y - distance;
		break;
	//east/west
	case 4:
		x = x - distance;
		break;
	case 6:
		x = x + distance;
		break;
	//south
	case 1:
		x = x - distance;
		y = y + distance;
		break;
	case 2:		
		y = y + distance;
		break;
	case 3:
		x = x + distance;
		y = y + distance;
		break;
	default:
		break;
	}

	return GetTile(x, y);

}

void Map::Console_Camera_Print(int x, int y, int w, int h, bool center)
{
	if (center == true)
	{
		//if centered, call function with coordinates at center of current screen
		Console_Camera_Print(x + w / 2, y + w / 2, w, h);
		return;
	}

	if (x < 0)
		x = 0;
	if (y < 0)
	{
		y = 0;
	}
	if (x + w >= width)
	{
		w = width - x;
	}
	if (y + h >= height)
	{
		h = height - y;
	}

	if (x >= width || y >= height)
		return;

	for (int i = y; i < y+h; i++)
	{
		for (int j = x; j < x+w; j++)
		{
			GetTile(j, i)->ConsolePrint();
			//cout << " ";

		}

		cout << "\n";
	}




	
}

void Map::DrawCamera(SDL_Renderer * Renderer, TileSet * set, int x, int y, int w, int h, bool center)
{
	if (center == true)
	{
		//if centered, call function with coordinates at center of current screen
		//DrawCamera(Renderer, set, x + w / 2, y + w / 2, w, h);
		//return;
	}

	
	

	//if (x >= width || y >= height)
		//return;

	for (int i = y; i < y + height; i++)
	{
		for (int j = x; j < x + width; j++)
		{
			
			if (GetTile(j, i) != NULL)
			{
				GetTile(j, i)->Render(Renderer, set, (j-x) * 32,(i-y) * 32);
			}
				
			
		}

		
	}
}
void Map::consolePrint()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			GetTile(x, y)->ConsolePrint();
			cout << " ";

		}

		cout << "\n";
	}
}




void Map::makeBorders()
{
	for (int x = 0; x < width; x++)
	{
		GetTile(x, 0)->setTile(cellType::CELL_BORDER);
		GetTile(x, height-1)->setTile(cellType::CELL_BORDER);
		
	}
	for (int y = 0; y < height; y++)
	{
		GetTile(0, y)->setTile(cellType::CELL_BORDER);
		GetTile(width - 1, y)->setTile(cellType::CELL_BORDER);
		
	}
}

bool Map::GenerateMap()
{
	Dungeon d = Dungeon(width-1, height-1);
	d.generate(50);
	string * str = d.Export();
	for (int x = 1; x < width-1; x++)
	{
		for (int y = 1; y < height-1; y++)
		{
			string s = str[(y-1)* (width - 1) + (x-1)];
			if ( s == " ")
			{
				GetTile(x, y)->setTile(cellType::CELL_FLOOR);
			}
			else if (s == "#")
			{
				GetTile(x, y)->setTile(cellType::CELL_WALL);
			}
			else if (s == "+"|| s == "-")
			{
				GetTile(x, y)->setTile(cellType::CELL_DOOR);
			}
			else if (s == ">")
			{
				GetTile(x, y)->setTile(cellType::CELL_UP);
				stairX = x;
				stairY = y;
			}
			else if (s == "<")
			{
				GetTile(x, y)->setTile(cellType::CELL_DOWN);
			}
			
			
		}
	}

	return true;

}

