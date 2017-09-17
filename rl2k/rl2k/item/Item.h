#pragma once
#include <string>
using namespace std;
class Item
{
public:
	Item();
	~Item();

	int itemLevel;
	double weight;
	string name;
	string description;
	string collection = "items";
	int spriteID = 0;	//once an item is created, its drawable will be loaded from here
	virtual string GetFullName() = 0;

	
	
};

