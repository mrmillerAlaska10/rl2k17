#pragma once
#include "Texture.h"
#include <vector>
using namespace std;
class Sprite;
class SpriteCollection
{
public:
	SpriteCollection();
	~SpriteCollection();
	void Load(string texture, SDL_Renderer * renderer);
	
	void Draw(int id, int x, int y, SDL_Renderer * renderer);
	void Draw(int id, int x, int y, int camX, int camY, SDL_Renderer * renderer);
	Texture * SourceTexture;
	vector<Sprite> Sprites;
};

