#pragma once
#include "Attachable.h"
#include "../../map/Level.h"
#include "../../util/Navigator.h"
#include "../../map/LevelState.h"
class Controller :
	public Attachable
{
public:
	Controller(Actor * actor);
	~Controller();
	string getID();

	virtual void ProcessInput(GameEvent e);
	bool Move(int moveX, int moveY);

	virtual levelState setState();

protected:
	Controller();
};

