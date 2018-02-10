#pragma once

class Ship
{

public:
	Ship();
	virtual ~Ship() = 0;
	void Action();
	void Move();

protected: 
	int CurrentDurability;
	int MaxDurability;
	int Speed;
	int Gold;
	

	virtual void DoMove() = 0;
	virtual void DoAction() = 0;

};
