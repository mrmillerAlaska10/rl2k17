#include "Drawable.h"
#include "../Actor.h"


Drawable::Drawable(Actor * a)
{
	this->Parent = a;
	ComponentID = "Drawable";
}

Drawable::~Drawable()
{
}

void Drawable::Draw(SDL_Renderer * renderer, SpriteCollection * sprites, int camX, int camY)
{
	sprites->Draw(spriteID, getOwner()->x, getOwner()->y, camX, camY, renderer);
	
}

string Drawable::getID()
{
	return ComponentID;
}
