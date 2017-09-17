#include "Actor.h"
#include "../ECS/Components/Entity.h"
#include <iostream>
#include "Components\ComponentManager.h"

Actor::Actor()
{
}


Actor::~Actor()
{
}

void Actor::shutdown(ComponentManager * c)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Shutdown();
		c->RemoveComponent(components[i]);
	}

	

}

void Actor::ProcessInput(SDL_Event & e)
{

}

void Actor::Draw(SDL_Renderer * Renderer)
{
	
}

Attachable * Actor::getComponent(string componentID)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->getID() == componentID)
		{
			return components[i];
		}
	}


	return nullptr;
}

void Actor::AddComponent(Attachable * component)
{
	if (getComponent(component->getID()) == nullptr)
	{
		components.push_back(component);
		component->setOwner(this);
	}
}

void Actor::Attack(Actor * target)
{
	Entity * attacker = (Entity*)getComponent("Entity");
	Entity * defender = (Entity*)target->getComponent("Entity");
	cout << attacker->name << " attacked " << defender->name;
}

