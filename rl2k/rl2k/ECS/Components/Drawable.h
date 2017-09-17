#pragma once
#include "Attachable.h"
#include "../../engine/graphics/SpriteBatch.h"
class Drawable :
	public Attachable
{
public:
	Drawable(Actor * a);
	~Drawable();
	void Draw(SDL_Renderer * renderer, SpriteCollection * sprites, int camX, int camY);
	string getID();
	int spriteID;
	string collection = "people";
};

