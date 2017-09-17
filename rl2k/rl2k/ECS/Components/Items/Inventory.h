#pragma once
#include "../Attachable.h"
#include "../../../item/Item.h"
#include <vector>
#include <iostream>
#include "../../../gui/GPanel.h"
using namespace std;
class Inventory :
	public Attachable
{
public:
	Inventory();
	Inventory(Actor * a);
	~Inventory();

	string getID();

	void addItem(Item * i);
	void echo();
	vector<Item*> items;

private:
	//use -1 for infinite
	int limit = -1;
	
};

