#include "aiController.h"



aiController::aiController(Actor	 * a)
{
	this->Parent = a;
	ComponentID = "aiController";
	

}


void aiController::ProcessInput(GameEvent e)
{
	
	
}


aiController::~aiController()
{
}

void aiController::active()
{
	int direction = rand() % 10 +1 ;
	Move(Navigator::getX(direction), Navigator::getY(direction));
	this->getOwner()->energy = 0;
}

levelState aiController::setState()
{
	return levelState::AI;
}
