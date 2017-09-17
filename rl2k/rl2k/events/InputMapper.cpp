#include "InputMapper.h"
#include "../util/Navigator.h"


InputMapper::InputMapper()
{
}


InputMapper::~InputMapper()
{
}

void InputMapper::Update(SDL_Event & e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		HandleMovement(e);
		HandleActions(e);
		break;
	default:
		break;
	}
}

void InputMapper::HandleMovement(SDL_Event & e)
{
	GameEvent moveEvent;
	moveEvent.eventType = USER_EVENT::ACTION_MOVE;
	switch (e.key.keysym.sym)
	{
	case SDLK_1:	
	case SDLK_KP_1:
		moveEvent.Direction = 1;
		break;
	case SDLK_2:
	case SDLK_KP_2:
		moveEvent.Direction = 2;
		break;
	case SDLK_3:
	case SDLK_KP_3:
		moveEvent.Direction = 3;
		break;
	case SDLK_4:
	case SDLK_KP_4:
		moveEvent.Direction = 4;
		break;
		break;
	case SDLK_6:
	case SDLK_KP_6:
		moveEvent.Direction = 6;
		break;
	case SDLK_7:
	case SDLK_KP_7:
		moveEvent.Direction = 7;
		break;
	case SDLK_8:
	case SDLK_KP_8:
		moveEvent.Direction = 8;
		break;
	case SDLK_9:
	case SDLK_KP_9:
		moveEvent.Direction = 9;
		break;	
	default:
		moveEvent.eventType = USER_EVENT::NO_ACTION;
		break;
	}
	if(moveEvent.eventType != USER_EVENT::NO_ACTION)
	events.push(moveEvent);
}
void InputMapper::HandleActions(SDL_Event & e)
{
	GameEvent ge;
	
	switch (e.key.keysym.sym)
	{		//Grab
	
	case SDLK_g:
	{
		ge.eventType = USER_EVENT::ACTION_GRAB;
		events.push(ge);
		break;
	}
	default:
		break;
	}
}
void InputMapper::pop()
{
	while (!events.empty())
	{
		events.pop();
	}
}
