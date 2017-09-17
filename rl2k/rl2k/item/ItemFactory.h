#pragma once
#include "Item.h"
#include "Wieldable.h"
#include <vector>
//Class for generating infinite use items like rods, consumable items like potions, and equipable weapons 
// and armor.
class ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();

	void LoadWeapons(string weaponData);
	void LoadArmor(string armorData);
	void LoadAccessories(string accessoryData);

	//non-consumable items are consumable items with a negative charge
	void loadOtherItems(string itemData);



	//generates anything
	Item * Generate();
	wieldable * GenerateWeapon();
	wieldable * GenerateBow();
	wieldable * GenerateArmor();
	Item * GenerateConsumable();
	Item * GenerateReusable();


	//All non artifact weapons are based off these. A magical weapon has bonus damage and maybe
	vector<wieldable> weaponBases;
	
};

