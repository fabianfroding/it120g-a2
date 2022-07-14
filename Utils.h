#pragma once

using namespace std;

class Utils
{

public:
	static int PromptForInputOption(string promptMessage, bool allowMultiNumber = false);
	static int PromptForNumber(string promptMessage);
	static bool IsMatching(char char1, char char2, char char3);
	static char* GenerateRandomSymbols(char randomSymbols[][3], char gameSymbols[3]);
	static int GetNumMatches(char randomSymbols[][3]);
	static int GetWinAmount(int numMatches, int betAmount);
};
