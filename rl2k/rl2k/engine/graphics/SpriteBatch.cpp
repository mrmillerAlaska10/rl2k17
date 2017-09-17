#include "SpriteBatch.h"
#include "Sprite.h"


SpriteCollection::SpriteCollection()
{
}


SpriteCollection::~SpriteCollection()
{
}

void SpriteCollection::Load(string texture,SDL_Renderer * renderer)
{
	SourceTexture = new Texture();
	SourceTexture->loadFromFile(texture, renderer);
	//texture dimensions
	int tWidth = SourceTexture->getWidth();
	int tHeight = SourceTexture->getHeight();
	//sprite dimensions 
	//needs to not be hard coded
	int sWidth = 16;
	int sHeight = 16;

	//cells
	int columns = tWidth / sWidth;
	int rows = tHeight / sHeight;

	for (int x = 0; x < columns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			Sprite s;
			int X = x* sWidth;
			int Y = y * sHeight;
			int W = sWidth;
			int H = sHeight;
			s.textureCoordinates = { X,Y,W,H };
			Sprites.push_back(s);
		}
	}

}

void SpriteCollection::Draw(int id, int x, int y, SDL_Renderer * renderer)
{
	SDL_Rect clip = Sprites[id].textureCoordinates;
	this->SourceTexture->render(x*32, y*32, renderer, &clip);
}

void SpriteCollection::Draw(int id, int x, int y, int camX, int camY,SDL_Renderer * renderer)
{
	SDL_Rect clip = Sprites[id].textureCoordinates;
	SDL_Rect quad = clip;
	clip.w = 32;
	clip.h = 32;

	this->SourceTexture->render((x - camX) * 32 , (y  - camY)*32, renderer, &clip, &quad);
}

