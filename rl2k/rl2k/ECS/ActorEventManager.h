#pragma once
#include <vector>
#include "../ECS/Actor.h"
class ActorEventManager
{
public:
	ActorEventManager();
	~ActorEventManager();

	void RegisterAttackAction(Attachable* component);
	void RegisterDefendAction(Attachable* component);
	void RegisterMoveAction(Attachable * component);

private:
	vector<Attachable*> Attackers;
	vector<Attachable*> Defenders;
	vector<Attachable*> Movers;


};

