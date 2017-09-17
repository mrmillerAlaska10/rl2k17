#pragma once
#include "../Attachable.h"

#include "../../../item/Item.h"
class GroundItem :
	public Attachable
{
public:
	GroundItem();
	~GroundItem();
	GroundItem(Actor * a); 
	void Shutdown();
	string getID();
	
	string GetName();
	Item * itemDefinition;
	
};

