#pragma once
enum levelState
{
	INIT,	//initial state
	PLAYER,	//active entity is a player and waiting for input
	MENU,	//active entity is a player who is in a menu
	AI,		//active entity is an ai, calculate action
	IDLE	//no active entity. Add energy to all entities
}; 
