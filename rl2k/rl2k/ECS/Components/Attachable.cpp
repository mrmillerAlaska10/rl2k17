#include "Attachable.h"



Attachable::Attachable()
{
}


Attachable::~Attachable()
{
	Shutdown();
}

void Attachable::ProcessInput(GameEvent e)
{
}

void Attachable::Update()
{
}

void Attachable::Draw(SDL_Renderer * renderer, SpriteCollection * sprites, int camX, int camY)
{
}



void Attachable::Load(xml_node<>* base)
{
}

void Attachable::Shutdown()
{
	Parent = nullptr;
	gameMap = nullptr;
}



void Attachable::setOwner(Actor * a)
{
	if(Parent == nullptr)
	this->Parent = a;
}

Actor * Attachable::getOwner()
{
	return this->Parent;
}

void Attachable::setOrder(Actor * actor)
{
}

void Attachable::setMap(Level * level)
{
	this->gameMap = level;
}
