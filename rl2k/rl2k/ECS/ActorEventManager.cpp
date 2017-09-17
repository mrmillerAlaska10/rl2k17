#include "ActorEventManager.h"



ActorEventManager::ActorEventManager()
{
}


ActorEventManager::~ActorEventManager()
{
}

void ActorEventManager::RegisterAttackAction(Attachable * component)
{
	Attackers.push_back(component);
}

void ActorEventManager::RegisterDefendAction(Attachable * component)
{
	Defenders.push_back(component);
}

void ActorEventManager::RegisterMoveAction(Attachable * component)
{
	Movers.push_back(component);
}
