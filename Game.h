#pragma once

class Game
{

public:
	Game()
	{
		moneyInserted = 0;
		moneyWon = 0;
		running = false;
		gameSymbols[0] = 'A';
		gameSymbols[1] = 'O';
		gameSymbols[2] = 'X';
	}

private:
	int moneyInserted;
	int moneyWon;
	bool running;
	char gameSymbols[3];

public:
	void Run();
	void PrintStats(bool showMoneyWon);
	
};
