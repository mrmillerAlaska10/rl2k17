#include "ComponentManager.h"
#include "../Actor.h"
#include "Drawable.h"
#include "Controller.h"
#include "Entity.h"
#include "aiController.h"
#include "Items\GroundItem.h"
#include "Items\Inventory.h"
#include <algorithm>    // std::find
ComponentManager::ComponentManager(SDL_Renderer * renderer, Level * level)
{
	sprites = new SpriteCollection();
	sprites->Load("img/DawnLike/Characters/Player0.png", renderer);
	batches["people"] = sprites;


	sprites = new SpriteCollection();
	sprites->Load("img/DawnLike/Items/MedWep.png", renderer);
	batches["weapons"] = sprites;
	referenceLevel = level;
}

ComponentManager::~ComponentManager()
{
}


bool ComponentManager::PrepareEntity(string name)
{
	Entity * e = new Entity();
	e->name = name;
	preppedAttachable = e;
	e->setMap(referenceLevel);
	return true;
}

bool ComponentManager::AttachPreparedComponent(Actor * actor)
{
	actor->AddComponent(preppedAttachable);
	preppedAttachable->setOwner(actor);
	return true;
}
bool ComponentManager::AddComponent(Actor * actor, string ComponentId)
{
	Attachable *createdComponent = 0;
	if (ComponentId == "Drawable")
	{
		Drawable * d = new Drawable(actor);
		d->spriteID = 0;
		actor->AddComponent(d);
		OnDraw.push_back(d);
		createdComponent = d;		
	}
	else if (ComponentId == "Controller")
	{
		Controller * c = new Controller(actor);
		
		actor->AddComponent(c);
		OnMovement.push_back(c);
		OnAction.push_back(c);
		createdComponent = c;
		
	}
	else if (ComponentId == "aiController")
	{
		aiController * a = new aiController(actor);

		actor->AddComponent(a);
		
		createdComponent = a;

	}
	else if (ComponentId == "Entity")
	{
		Entity * e = new Entity(actor);
		createdComponent = e;
	}
	else if (ComponentId == "GroundItem")
	{
		GroundItem * gi = new GroundItem(actor);
		actor->AddComponent(gi);
		createdComponent = gi;
	}
	else if (ComponentId == "Inventory")
	{
		Inventory * inv = new Inventory(actor);
		actor->AddComponent(inv);
		createdComponent = inv;
	}
	createdComponent->setMap(referenceLevel);
	
	return false;
}

void ComponentManager::RemoveComponent(Attachable * attached)
{
	attached->Shutdown();
	std::vector<Attachable *>::iterator it;

	it = find(OnDraw.begin(), OnDraw.end(), attached);
	if (it != OnDraw.end())
	{
		OnDraw.erase(it);		
	}

	it = find(OnUpdate.begin(), OnUpdate.end(), attached);
	if (it != OnUpdate.end())
	{
		OnUpdate.erase(it);
	}

	it = find(OnMovement.begin(), OnMovement.end(), attached);
	if (it != OnMovement.end())
	{
		OnMovement.erase(it);
	}

	it = find(OnAction.begin(), OnAction.end(), attached);
	if (it != OnAction.end())
	{
		OnAction.erase(it);
	}

	it = find(Deleteable.begin(), Deleteable.end(), attached);
	if (it != Deleteable.end())
	{
		Deleteable.erase(it);
	}
	delete attached;

}

void ComponentManager::pushEvent(GameEvent e)
{
	if (e.eventType == USER_EVENT::ACTION_MOVE)
	{
		for (int i = 0; i < OnMovement.size(); i++)
		{
			OnMovement[i]->ProcessInput(e);
		}
	}
	if (e.eventType == USER_EVENT::ACTION_GRAB)
	{
		for (int i = 0; i < OnAction.size(); i++)
		{
			OnAction[i]->ProcessInput(e);
		}
		
	}
}

void ComponentManager::Update()
{

}

void ComponentManager::Draw(SDL_Renderer * renderer, int camX, int camY)
{
	for (int i = 0; i < OnDraw.size(); i++)
	{
		Drawable * d = (Drawable*)OnDraw[i];
		string collection = d->collection;
		OnDraw[i]->Draw(renderer, this->batches[collection], camX, camY);
	}
}

