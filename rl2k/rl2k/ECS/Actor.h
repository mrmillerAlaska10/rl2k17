#pragma once
#include <string>
#include <vector>
#include "../ECS/Components/Attachable.h"
#include <SDL.h>
#include "Components\ComponentManager.h"
using namespace std;
class Actor
{
public:
	Actor();
	~Actor();
	void shutdown(ComponentManager *);
	int x, y;
	int energy;
	void ProcessInput(SDL_Event &e);
	void Draw(SDL_Renderer * Renderer);	
	Attachable* getComponent(string componentID);
	void AddComponent(Attachable * component);
	

	//events
	void Attack(Actor * target);

	
private:
	vector<Attachable*> components;
	string actorID;
};

