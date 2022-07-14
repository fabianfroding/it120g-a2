#pragma once

class Player
{

public:
	Player()
	{
		Money = 0;
	}

private:
	int Money; // Available money.

public:
	int GetMoney();
	void AddMoney(int amount);

};
