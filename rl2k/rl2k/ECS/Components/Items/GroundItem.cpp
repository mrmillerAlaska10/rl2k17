#include "GroundItem.h"



GroundItem::GroundItem()
{
}

GroundItem::GroundItem(Actor * a)
{
	this->Parent = a;
	
	ComponentID = "GroundItem";
}

void GroundItem::Shutdown()
{
	Attachable::Shutdown();
	
	itemDefinition = nullptr;
}

string GroundItem::getID()
{
	return "GroundItem";
}

string GroundItem::GetName()
{
	
	return itemDefinition->GetFullName();
}


GroundItem::~GroundItem()
{
	int z = 3;
}
