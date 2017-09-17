#include "Wieldable.h"
#include <sstream>


wieldable::wieldable()
{
}


wieldable::~wieldable()
{
}

string wieldable::GetFullName()
{
	string text = this->name + getBonus();

	return text;
}

string wieldable::getBonus()
{
	//(xdy) [armor, evasion, life] <+hit, +dam> {+bonus}
	string tag = "";
	//weapon
	if (this->diceCount != 0)
	{
		int netSize = diceSize + bonusDiceSize;
		int netCount = diceCount + bonusDice;
		stringstream sstr;
		sstr <<  "(" << netSize << "d" << netCount << ")";
		string diceTag = sstr.str();
		tag += diceTag;
	}

	if (this->bonusDamage != 0|| this->bonusHit != 0)
	{
		stringstream sstr;
		string symbol = "+";
		string symbol2 = symbol;

		if (bonusHit < 0)
			symbol = "-";
		if (bonusDamage < 0)
			symbol2 = "-";

		sstr << "< " <<symbol << bonusHit << ", " << symbol2 << bonusDamage << ">";
		tag += sstr.str();
	}

	//armor
	if (this->Life != 0 || this->evasion != 0 || this->damageReduction != 0)
	{
		stringstream sstr;
		string symbol = "+";
		string symbol2 = symbol;
		string symbol3 = symbol;

		if (Life +  bonusLife < 0)
			symbol = "-";
		if (evasion + bonusEvasion < 0)
			symbol2 = "-";
		if (damageReduction + bonusDamageReduction < 0)
			symbol3 = "-";

		sstr << "[ " << symbol << Life + bonusLife << ", " << symbol2 << evasion + bonusEvasion << ", " << symbol3 << damageReduction + bonusDamageReduction << "]";
		tag += sstr.str();
	}

	

	return tag;
}
