#pragma once
#include <string>
#include "Custom_Events.h"
class Actor;
using namespace std;
struct GameEvent
{
	USER_EVENT eventType = USER_EVENT::NO_ACTION;
	Actor * generator = 0;
	int Direction = -1;
};