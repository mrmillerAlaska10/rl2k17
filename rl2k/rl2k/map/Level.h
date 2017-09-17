#pragma once
#include "Map.h"
#include "TileSet.h"
#include "Camera.h"
#include "../ECS/Actor.h"
#include <vector>
#include "../ECS/Components/ComponentManager.h"
#include "../events/InputMapper.h"
#include "LevelState.h"
#include "../gui/GBase.h"
using namespace std;
class Level
{
public:
	Level(GBase * ui);
	~Level();

	void createGameUI(SDL_Renderer * renderer, GBase * gb);

	

	void Gen(SDL_Renderer * renderer);	
	void ProcessInput(SDL_Event &e);	
	void UpdateGame();
	

	void DrawGame(SDL_Renderer * Renderer);
	void Shutdown();
	ComponentManager * getComponentManager();
	Map * getMap();
	bool addActor(Actor * a, bool ignoresCollision = false);	
	bool addItem(Actor * a);
	void removeActor(Actor * A);
	void SpawnPlayer(int x, int y);	
	/**
	*   \brief Move an actor on the map.
	*
	*   Attempts to change the position of an actor on the map while dealing
	*	with tile and actor collision. 
	*
	*   \param actor The actor being moved
		\param direction Numpad based direction. 7 is NW, 8 is N, 2 is S, etc
		\param collided List of Actors hit on way to final destination
		\param distance How far the actor will attempt to move
		\bool xray Will attempt to move through Actors. Will not move if there is an actor on final square
	*   \return An int
	*
	**/
	int MoveActor(Actor * actor, int direction, vector<Actor*>&collided, int distance = 1, bool xray = false);

	levelState levelState;
	GBase * ui;
private:
	
	Actor * activeActor = 0;
	InputMapper input;
	Map* map;
	TileSet * tiles;
	ComponentManager * components;
	Camera * Cam;
	vector<Actor*> actors;
	vector<Actor*> items;

	
};

