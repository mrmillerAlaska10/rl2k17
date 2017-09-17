#pragma once
#include "Item.h"
#include <string>
using namespace std;
class wieldable :
	public Item
{
public:
	wieldable();
	~wieldable();

	string GetFullName();
	string getBonus();
	///Weapn properties
	//easy function for damage. Add other effects of attacking as an onAttackEffect
	string DamageExpression;

	//number of times to roll the dice
	int diceCount = 1;
	

	//the size of the dice being rolled
	int diceSize = 1;
	int bonusDiceSize = 0;	

	//deals with accuracy
	int hit = 1;
	


	//bonuses from being magical items
	int bonusDice = 1;
	int bonusDamage = 1;
	int bonusHit = 1;

	///armor properties
	int Life =1;
	int evasion = 1;
	int damageReduction = 1;
	
	//magic armor bonuses
	int bonusLife = 1;
	int bonusEvasion = 1;
	int bonusDamageReduction = 10;

};

