#pragma once
#include "../../map/Level.h"
#include "../../item/ItemFactory.h"
#include "../Components/Items/GroundItem.h"
class Spawner
{
public:
	Spawner();
	~Spawner();

	

	void SpawnMonsters(Level *zone, int count = 3);
	void SpawnItems(Level * zone, int count = 3);

	Actor * GenerateItem(ComponentManager * components);
	void PopulateItem(GroundItem * groundItem);
	Actor * GenerateMonster(ComponentManager * components);

private:
	void initBluePrints();
	ItemFactory itemFactory;
};

