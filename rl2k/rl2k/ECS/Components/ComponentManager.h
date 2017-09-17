#pragma once

#include "Attachable.h"
#include <vector>
#include <queue>
#include<string>
#include "../../events/GameEvent.h"
#include <map>
using namespace std;



class ComponentManager
{
public:
	
	ComponentManager(SDL_Renderer * renderer, Level * level);
	~ComponentManager();

	bool PrepareEntity(string name);

	bool AttachPreparedComponent(Actor * actor);

	bool AddComponent(Actor * actor, string ComponentId);
	void RemoveComponent(Attachable *);
	void pushEvent(GameEvent e);

	void Update();
	void Draw(SDL_Renderer * renderer, int camX, int camY);
	

private:
	vector<Attachable *> OnDraw;
	vector<Attachable*> OnUpdate;
	vector<Attachable*> OnMovement;

	//For things like casting spells, grabbing items, kicking, opening etc
	vector<Attachable*> OnAction;

	//These are entities that will be removed
	vector<Attachable*> Deleteable;
	queue<GameEvent> events;
	Level * referenceLevel;
	Attachable * preppedAttachable;
	
	map<string, SpriteCollection* > batches;
	SpriteCollection * sprites;
	SpriteCollection * items;
};

