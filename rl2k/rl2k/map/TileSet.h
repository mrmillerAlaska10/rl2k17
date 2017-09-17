#pragma once
#include <SDL.h>
#include "../engine/graphics/Texture.h"
class TileSet
{
public:
	TileSet();
	
	
	TileSet(string imageSource, SDL_Renderer * Renderer, int cellWidth, int cellHeight);
	~TileSet();

	void Render(SDL_Renderer * Renderer, int cellID, int x, int y);
	

private:
	Texture * sourceImage;
	int cellW, cellH;
	SDL_Rect ** cells;
};

