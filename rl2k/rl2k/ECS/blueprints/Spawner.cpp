#include "Spawner.h"
#include "../Components/Drawable.h"
#include "../Components/aiController.h"
Spawner::Spawner()
{
	initBluePrints();
}


Spawner::~Spawner()
{
}

void Spawner::initBluePrints()
{
	
	itemFactory.LoadWeapons("point");
}

struct tpair
{
	int x, y;
};
void Spawner::SpawnMonsters(Level *zone, int count)
{
	Map* map = zone->getMap();
	vector<tpair> openTiles;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (map->GetTile(i, j)->getType() == cellType::CELL_FLOOR)
			{				
				tpair t = tpair{ i, j };
				openTiles.push_back(t);
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		Actor * m = GenerateMonster(zone->getComponentManager());
		
		int r = rand() % openTiles.size();
		m->x = openTiles[r].x;
		m->y = openTiles[r].y;

		zone->addActor(m);
	}
}

void Spawner::SpawnItems(Level * zone, int count)
{
	Map* map = zone->getMap();
	vector<tpair> openTiles;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (map->GetTile(i, j)->getType() == cellType::CELL_FLOOR)
			{				
				tpair t = tpair{ i, j };
				openTiles.push_back(t);
			}
		}
	}

	for (int i = 0; i < count; i++)
	{
		Actor * item = GenerateItem(zone->getComponentManager());
		int r = rand() % openTiles.size();
		item->x = openTiles[r].x;
		item->y = openTiles[r].y;

		zone->addItem(item);
	}
}

Actor * Spawner::GenerateItem(ComponentManager * components)
{
	Actor * newItem = new Actor(); 
	components->AddComponent(newItem, "Drawable");
	components->AddComponent(newItem, "GroundItem");
	PopulateItem((GroundItem*)newItem->getComponent("GroundItem"));
	
	return newItem;
}

//attaches properties to a ground item
void Spawner::PopulateItem(GroundItem* groundItem)
{
	
	
	groundItem->itemDefinition = itemFactory.GenerateWeapon();
	Drawable * d = (Drawable*)groundItem->getOwner()->getComponent("Drawable");
	d->spriteID = groundItem->itemDefinition->spriteID;
	d->collection = groundItem->itemDefinition->collection;
}

Actor * Spawner::GenerateMonster(ComponentManager * components)
{
	Actor * newMonster = new Actor();
	components->AddComponent(newMonster, "Drawable");
	components->PrepareEntity("monster");
	components->AttachPreparedComponent(newMonster);
	components->AddComponent(newMonster, "aiController");

	return newMonster;
}
