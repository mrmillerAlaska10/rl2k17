#pragma once
#include <queue>
using namespace std;
enum USER_EVENT
{
	NO_ACTION,
	//Movement events
	ACTION_MOVE,
	//Action events
	ACTION_REST,	//rest to restore hp/mana
	ACTION_CONSUME, //consume food/potions
	ACTION_ACTIVATE_ITEM,
	ACTION_ACTIVATE_SPELL,
	ACTION_WIELD,
	ACTION_UNWIELD,
	ACTION_KICK,
	ACTION_THROW,
	ACTION_GRAB,	//put item on groun in inventory
	ACTION_INSPECT		//examing feature
};
