#pragma once
#include "Controller.h"
class aiController :
	public Controller
{
public:
	aiController(Actor * a);
	void ProcessInput(GameEvent e);
	~aiController();

	void active();


	levelState setState();
};

