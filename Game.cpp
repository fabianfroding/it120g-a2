#include <iostream>
#include "Game.h"
#include "Utils.h"

using namespace std;

void Game::Run()
{
	// One-time execution of the beginning of the game loop.
	cout << " ~ ~ Welcome to One-armed Bandit ~ ~ ";
	running = true;

	while (running) {
		PrintStats(true);

		int betOption = Utils::PromptForInputOption("\n\nChoose option: \n1. Insert 100:-\n2. Insert 300:-\n3. Insert 500:-\n4. Skip\n5. Quit");
		int amountToInsert = 0;

		switch (betOption)
		{
		case 1:
			amountToInsert = 100;
			break;
		case 2:
			amountToInsert = 300;
			break;
		case 3:
			amountToInsert = 500;
			break;
		case 4:
			break;
		case 5:
			running = false;
			continue;
			break;
		default:
			system("cls");
			cout << "\n\nInvalid option. Please choose a valid option...";
			continue;
		}

		moneyInserted += amountToInsert;
		if (moneyInserted <= 0)
		{
			system("cls");
			cout << "\n\nYou have no money inserted. Please insert some money.";
			continue;
		}

		PrintStats(false);
		
		// Prompt for amount to bet.
		int betAmount = 0;
		while (betAmount <= 0)
		{
			betAmount = Utils::PromptForNumber("\n\nType in the amount of money you want to bet:");
			if (betAmount < 0)
			{
				cout << "\n\nInvalid input.\n";
			}
		}

		if (betAmount > moneyInserted)
		{
			system("cls");
			cout << "\n\nYou can not bet more money than what you have inserted.";
			continue;
		}
		else
		{
			moneyInserted -= betAmount;
		}

		// Generate random symbols.
		char randomSymbols[3][3];
		Utils::GenerateRandomSymbols(randomSymbols, gameSymbols);

		// Get number of matching rows, columns and diagonals.
		int numCorrectMatches = Utils::GetNumMatches(randomSymbols);

		int winAmount = Utils::GetWinAmount(numCorrectMatches, betAmount);
		if (winAmount <= 0)
		{
			cout << "\n\nNo matches. Try again.";
		}
		else
		{
			cout << "\n\n" << numCorrectMatches << " matches! You won " << winAmount << " money!";
			moneyWon += winAmount;
		}
	}

}

void Game::PrintStats(bool showMoneyWon)
{
	cout << "\n\nTotal money inserted: " << moneyInserted;
	if (moneyWon > 0 && showMoneyWon)
	{
		cout << "\nTotal money won: " << moneyWon;
	}
}
