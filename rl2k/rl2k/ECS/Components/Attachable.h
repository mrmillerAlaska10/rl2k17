#pragma once
#include <string>
#include <vector>
#include <rapidxml.hpp>
#include <SDL.h>
#include "../../engine/graphics/SpriteBatch.h"
#include "../../events/GameEvent.h"
using namespace std;
using namespace rapidxml;
class Actor;
class Level;
class Attachable
{
public:
	Attachable();
	~Attachable();

	virtual void ProcessInput(GameEvent e);
	virtual void Update();
	virtual void Draw(SDL_Renderer * renderer, SpriteCollection * sprites, int camX, int  camY);
	virtual void Load(xml_node<> *base);
	virtual void Shutdown();
	virtual string getID() = 0;
	void setOwner(Actor * a);
	Actor * getOwner();
	void setOrder(Actor * actor);
	void setMap(Level * level);
protected:
	string ComponentID;
	Actor * Parent;
	Level * gameMap;
private:
	


};

