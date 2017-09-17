#include "Controller.h"
#include "Items\GroundItem.h"
#include "../../item/Wieldable.h"
#include "Items\Inventory.h"


Controller::Controller(Actor * a)
{
	this->Parent = a;
	ComponentID = "Controller";
}

Controller::~Controller()
{
}

string Controller::getID()
{
	return "Controller";
}

void Controller::ProcessInput(GameEvent e)
{
	if (e.eventType == USER_EVENT::ACTION_MOVE)
	{
		int direction = e.Direction;
		Move(Navigator::getX(direction), Navigator::getY(direction));
	}
	if (e.eventType == USER_EVENT::ACTION_GRAB)
	{
		Cell * c = this->gameMap->getMap()->GetTile(Parent->x, Parent->y);
		if (c->getAttachedItem() != nullptr)
		{
			GroundItem * g = (GroundItem*)c->getAttachedItem()->getComponent("GroundItem");
			c->RemoveItem();
			cout<< "grabbed " << g->GetName() << endl;
			
			Inventory * inv = (Inventory*)this->Parent->getComponent("Inventory");
			if (inv != nullptr)
			{

				inv->addItem(g->itemDefinition);
				cout << "items: \n";
				inv->echo();
				cout << endl;
			}

			gameMap->removeActor(g->getOwner());
			gameMap->ui->Refresh();
		}
	}
}

bool Controller::Move(int moveX, int moveY)
{
	vector<Actor*> collided;
	int distance = this->gameMap->MoveActor(getOwner(), Navigator::getDirection(moveX, moveY), collided);
	if(collided.size() != 0)
	{
		for (int i = 0; i < collided.size(); i++)
		{
			this->getOwner()->Attack(collided[i]);
		}
		getOwner()->energy = 0;
	}
	else
	{
		getOwner()->energy = 0;
	}
	
	return true;
}

levelState Controller::setState()
{
	return levelState::PLAYER;
}

Controller::Controller()
{
}
