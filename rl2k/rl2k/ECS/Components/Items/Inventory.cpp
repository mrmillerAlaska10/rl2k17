#include "Inventory.h"


Inventory::Inventory()
{
}

Inventory::Inventory(Actor * a)
{
	this->Parent = a;

	ComponentID = "Inventory";
}


Inventory::~Inventory()
{
}

string Inventory::getID()
{
	return "Inventory";
}

void Inventory::addItem(Item * i)
{
	items.push_back(i);
}

void Inventory::echo()
{
	for (int i = 0; i < items.size(); i++)
	{
		cout << items[i]->name;
	}
}
