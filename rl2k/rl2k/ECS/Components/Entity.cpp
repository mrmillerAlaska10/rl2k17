#include "Entity.h"



Entity::Entity()
{
}

Entity::Entity(Actor * a)
{
	this->Parent = a;
	ComponentID = "Entity";
}


Entity::~Entity()
{
}

string Entity::getID()
{
	return "Entity";
}
