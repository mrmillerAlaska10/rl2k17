#include "Level.h"
#include "../ECS/blueprints/Spawner.h"
#include "../ECS/Components/Controller.h"
#include "../ECS/Components/aiController.h"
#include "../ECS/Components/Drawable.h"
#include "../gui/GMenu.h"
#include "../ECS/Components/Items/Inventory.h"
Level::Level(GBase * ui)
{
	levelState = levelState::INIT;
	this->ui = ui;
}


Level::~Level()
{
}

void Level::createGameUI(SDL_Renderer * renderer, GBase * gb)
{
	GMenu* menu = new GMenu(renderer, 0, 0, 200, 200);
	menu->Init();
	menu->onRefresh = [menu]() {
		//Inventory* inv = (Inventory*)a->getComponent("Inventory");
		//vector<Item*> items = inv->items;
		//menu->load(items);
		//cout << "refresh echo: \n";
		//inv->echo();
		//cout << "\nend refresh\n";

	};
	
	GMessage * gm = new GMessage(renderer);
	
	menu->toggleVisibility();
	menu->toggleVisibility();
	gb->addRoot(menu);
	ui = gb;
}

void Level::Gen(SDL_Renderer * renderer)
{
	map = new Map();
	map->ConstructBlank(40, 40);
	tiles = new TileSet("img/terrain.png", renderer, 32,32 );
	Cam = new Camera(0, 0, 30, 30, 40,40);
	this->map->consolePrint();

	
	//load game sprites
	components = new ComponentManager(renderer, this);
	//debug actor
	Actor * deb = new Actor();
	deb->x = map->stairX;
	deb->y = map->stairY;
	Cam->set(0, 0);
	components->AddComponent(deb, "Drawable");
	components->AddComponent(deb, "Controller");
	components->AddComponent(deb, "Inventory");
	//components->AddComponent(deb, "Entity");
	components->PrepareEntity("player");
	components->AttachPreparedComponent(deb);
	Drawable* d = (Drawable*)deb->getComponent("Drawable");
	d->spriteID = 1;
	this->addActor(deb, true);
	Spawner s;
	s.SpawnMonsters(this, 1);
	s.SpawnItems(this, 4);
	

	int z = 0;
	

	

	
}

void Level::ProcessInput(SDL_Event &e)
{
	input.Update(e);
}
void Level::UpdateGame()
{
	if (activeActor != 0)
	{
		if (activeActor->energy <= 0)
		{
			levelState = levelState::IDLE;
		}
	}
	bool d = false;
	switch (levelState)
	{
	case INIT:
		levelState = levelState::IDLE;
		break;
	case PLAYER:
		if (!input.events.empty())
		{
			components->pushEvent(input.events.front());
			input.pop();
			cout << actors[0]->x << "," << actors[0]->y << "\n";
			
			
		}
		
		break;
	case MENU:
		break;
	case AI:
	{
		GameEvent g;
		aiController * a = (aiController*)activeActor->getComponent("Controller");
		a->active();
		cout << "ai turn";

		break;
	}
	case IDLE:
		//figure out whos turn it is next
		
		while (!d)
		{
			for each(Actor * a in actors)
			{
				if (!d)
				{
					a->energy++;
					if (a->energy > 50)
					{
						activeActor = a;
						Controller* c = (Controller*)a->getComponent("Controller");
						levelState = c->setState();
						d = true;
					}
				}
			}
		}		
		break;
	default:
		break;
	}
	
	Cam->set(actors[0]->x, actors[0]->y);
	
	getComponentManager()->Update();
}



void Level::DrawGame(SDL_Renderer * renderer)
{
	map->DrawCamera(renderer, this->tiles, Cam->position.x, Cam->position.y,40,40);
	for (int i = 0; i < actors.size(); i++)
	{
		components->Draw(renderer, Cam->position.x, Cam->position.y);
	}
	
}


void Level::Shutdown()
{
}

ComponentManager * Level::getComponentManager()
{
	return components;
}

Map * Level::getMap()
{
	return map;
}

bool Level::addActor(Actor * a, bool ignoresCollision)
{
	Cell * t = this->getMap()->GetTile(a->x, a->y);
	//cells only support 1 actor
	if (t->getAttachedActor() != nullptr)
	{
		return false;
	}
	//do collision checks on terrain
	if (!ignoresCollision)
	{
		if (!t->IsWalkable(t->getType()))
		{
			return false;
		}
	}
	
	t->AttachActor(a);
	this->actors.push_back(a);

	return true;
}

bool Level::addItem(Actor * a)
{
	Cell * t = this->getMap()->GetTile(a->x, a->y);
	if (t->getAttachedItem() != nullptr)
	{
		return false;
	}
	
	if (!t->IsWalkable(t->getType()))
	{
		return false;
	}

	t->AttachItem(a);
	this->items.push_back(a);


}

void Level::removeActor(Actor * A)
{
	//remove frm map
	if (A->getComponent("groundItem") == nullptr)
	{
		this->getMap()->GetTile(A->x, A->y)->RemoveActor();
	}
	else
	{
		this->getMap()->GetTile(A->x, A->y)->RemoveItem();
	}

	A->shutdown(getComponentManager());
	delete A;

	

	
}

void Level::SpawnPlayer(int x, int y)
{
	Actor * actor = new Actor();
}

int Level::MoveActor(Actor * actor, int direction, vector<Actor*> &collided, int distance, bool xray)
{
	for (int i = 0; i < distance; i++)
	{
		Cell * current = map->GetTile(actor->x, actor->y);
		Cell * c = map->GetTile(actor->x, actor->y, direction, distance);
		if (c->IsWalkable(c->getType(),true))
		{
			current->RemoveActor();
			c->AttachActor(actor);
			actor->x = c->x;
			actor->y = c->y;
		}
		else
		{
			if (c->getAttachedActor() != nullptr)
			{
				collided.push_back(c->getAttachedActor());
			}
			return i;
		}
	}

	return distance;

	return 0;
}
