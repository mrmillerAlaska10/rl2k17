#pragma once
#include "Attachable.h"
class Entity :
	public Attachable
{
public:
	Entity();
	Entity(Actor* a);
	~Entity();

	string getID();
	string name;

protected:

};

