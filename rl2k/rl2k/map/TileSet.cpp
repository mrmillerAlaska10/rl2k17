#include "TileSet.h"



TileSet::TileSet()
{
}


TileSet::TileSet(string imageSource, SDL_Renderer * renderer, int cellWidth, int cellHeight)
{
	this->cellW = cellWidth;
	this->cellH = cellHeight;
	this->sourceImage = new Texture();
	sourceImage->loadFromFile(imageSource, renderer);
	int imgW = sourceImage->getWidth();
	int imgH = sourceImage->getHeight();
	int cellRows = imgW / cellW;
	int cellColumns = imgH / cellH;
	cells = new SDL_Rect*[cellRows * cellColumns];
	for (int x = 0; x < cellRows; x++)
	{
		for (int y = 0; y < cellColumns; y++)
		{
			int c = y * cellColumns + x;
			this->cells[c] = new SDL_Rect();
			cells[c]->w = cellW;
			cells[c]->h = cellH;
			cells[c]->x = x*32; 
			cells[c]->y = y*32;
		}
	}
	
}

TileSet::~TileSet()
{
}

void TileSet::Render(SDL_Renderer * Renderer, int cellID, int x, int y)
{
	sourceImage->render(x, y, Renderer, cells[cellID]);
}
