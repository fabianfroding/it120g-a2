#include <iostream>
#include <string>
#include "Utils.h"

using namespace std;

// Reusable utility function for reading input from the player.
// Prints info to the player, wait for input.
// If the input is invalid it will return -1,
// which will be handled as invalid in the main game loop.
int Utils::PromptForInputOption(string promptMessage, bool allowMultiNumber)
{
	string input;
	cout << promptMessage << "\n";
	cin >> input;
	cout << "\n\n";

	if (input.length() != 1 && !allowMultiNumber)
	{
		return -1;
	}

	return input[0] - '0';
}

// Function to ask for a "free" number input".
int Utils::PromptForNumber(string promptMessage)
{
	string input;
	cout << promptMessage << "\n";
	cin >> input;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!isdigit(input[i])) {
			return -1;
		}
	}
	return stoi(input);
}

// Checks that 3 symbols are equal.
bool Utils::IsMatching(char char1, char char2, char char3)
{
	// We only need to do 2 comparisons here since if char2 and char3 are equal to char1, then char2 must be equal to char3.
	return char1 == char2 && char1 == char3;
}

// Generates random symbols based on the symbosl defined for the game and prints them out in a 3x3 matrix.
char* Utils::GenerateRandomSymbols(char randomSymbols[][3], char gameSymbols[3])
{
	for (size_t i = 0; i < 3; i++)
	{
		cout << "\n";
		for (size_t j = 0; j < 3; j++)
		{
			int random = rand() % 3;
			randomSymbols[i][j] = gameSymbols[random];
			cout << " " << randomSymbols[i][j] << " ";
		}
	}
	return *randomSymbols;
}

// Function to check for number of matching rows, columns or diagonals.
// This function is not dynamic and is only designed for a 3x3 matrix.
int Utils::GetNumMatches(char randomSymbols[][3])
{
	int numCorrectMatches = 0;

	// Check rows
	if (Utils::IsMatching(randomSymbols[0][0], randomSymbols[0][1], randomSymbols[0][2])) numCorrectMatches++;
	if (Utils::IsMatching(randomSymbols[1][0], randomSymbols[1][1], randomSymbols[1][2])) numCorrectMatches++;
	if (Utils::IsMatching(randomSymbols[2][0], randomSymbols[2][1], randomSymbols[2][2])) numCorrectMatches++;
	// Check columns
	if (Utils::IsMatching(randomSymbols[0][0], randomSymbols[1][0], randomSymbols[2][0])) numCorrectMatches++;
	if (Utils::IsMatching(randomSymbols[0][1], randomSymbols[1][1], randomSymbols[2][1])) numCorrectMatches++;
	if (Utils::IsMatching(randomSymbols[0][2], randomSymbols[1][2], randomSymbols[2][2])) numCorrectMatches++;
	// Check diagonals
	if (Utils::IsMatching(randomSymbols[0][0], randomSymbols[1][1], randomSymbols[2][2])) numCorrectMatches++;
	if (Utils::IsMatching(randomSymbols[0][2], randomSymbols[1][1], randomSymbols[2][0])) numCorrectMatches++;

	return numCorrectMatches;
}

// Function to calculate win amount based on number of matches.
int Utils::GetWinAmount(int numMatches, int betAmount)
{
	int winAmount = 0;
	int winMultiplier = 1;
	if (numMatches > 0) {
		if (numMatches <= 4) {
			winMultiplier = numMatches + 1;
		}
		else if (numMatches == 5) {
			winMultiplier = 7;
		}
		else {
			winMultiplier = 10;
		}
		winAmount = betAmount * winMultiplier;
	}
	return winAmount;
}
