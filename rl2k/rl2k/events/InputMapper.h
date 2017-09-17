#pragma once
#include "GameEvent.h"
#include "Custom_Events.h"
#include <SDL.h>
#include <queue>
using namespace std;
enum InputState
{
	INPUT_WAIT,
	INPUT_CAMERA,
	INPUT_UI,
	INPUT_MOVE,
	INPUT_AIM
};

class InputMapper
{
public:
	InputMapper();
	~InputMapper();
	InputState state = INPUT_MOVE;
	void Update(SDL_Event & e);
	void HandleMovement(SDL_Event & e);
	void HandleActions(SDL_Event & e);
	void pop();
	queue<GameEvent> events;

	
};

