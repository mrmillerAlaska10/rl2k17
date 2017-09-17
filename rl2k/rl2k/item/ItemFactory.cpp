#include "ItemFactory.h"
#include "../ThirdParty/json.hpp"
#include <fstream>
using json = nlohmann::json;
using namespace std;
ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}

void ItemFactory::LoadWeapons(string weaponData)
{
	//collection of weapons to use as a base. magical weapons may add modifiers
	vector<wieldable> wieldables;
	string a;
	//load the file
	std::ifstream i("data/Weapons.dat");

	json file;
	i >> file;

//	std::ofstream o("pretty.json");
//	o << std::setw(4) << file << std::endl;


	//each weapon should be a json object
	vector<json> v = file;
	for (int i = 0; i < v.size(); i++)
	{
		json jw = v[i];
		wieldable  w = wieldable();

		
		if (jw.find("name") != jw.end())
		{
			w.name = jw["name"];
		}
		if (jw.find("description") != jw.end())
		{
			w.description = jw["description"];
		}
		
		if (jw.find("category") != jw.end())
		{
			w.collection = jw["category"];
		}

		if (jw.find("damage") != jw.end())
		{
			w.DamageExpression = jw["damage"];
		}

		if (jw.find("level") != jw.end())
		{
			w.itemLevel = jw["level"];
		}

		if (jw.find("weight") != jw.end())
		{
			w.weight = jw["weight"];
		}

		

		if (jw.find("icon") != jw.end())
		{
			w.spriteID = jw["icon"];
		}
		
		wieldables.push_back(w);
		
	}

	this->weaponBases = wieldables;


	
	
}

wieldable *  ItemFactory::GenerateWeapon()
{
	//CHANCES
	const int NORMAL = 40;
	const int MAGIC = 9;
	const int ARTIFACT = 1;

	//int rarity = rand() % (NORMAL + MAGIC + ARTIFACT);
	wieldable  w = weaponBases[rand() % weaponBases.size()];
	//if (rarity < NORMAL)
	//{
		//int bonusDiceSize = rand() % 20;
		//w.bonusDiceSize = bonusDiceSize;
		
	//}


	return new wieldable(w);
}
