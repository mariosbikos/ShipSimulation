#include "Ship.h"

void Ship::Move()
{
	//pre-move. Standard things all ships do before they move
	this->DoMove(); //each subclass can do different things
	//after-move. Standard things all ships do after they move
}

Ship::Ship()
{

}

void Ship::Action()
{
	this->DoAction();
}

