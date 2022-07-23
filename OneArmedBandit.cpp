#include <iostream>
#include <string>

using namespace std;

/*============================================================
	VARIABLE DECLARATIONS
============================================================*/

const int NUM_COLS = 3;
const int NUM_ROWS = 3;
const char GameSymbols[3] = { 'A', 'O', 'X' };

/*============================================================
	PROCEDURE AND FUNCTIONAL DECLARATIONS AND DEFINITIONS
============================================================*/

/*	Reusable function for reading option-input chosen by the player.
	Returns an integer corresponding the the chosen option if valid, else return -1. */
int PromptForInputOption(string promptMessage, int numOptions) {
	string input;
	cout << promptMessage << "\n";
	cin >> input;
	cout << "\n\n";
	int result = input[0] - '0';

	if (input.length() != 1 || result < 1 || result > numOptions) {
		system("cls");
		cout << "\n\nInvalid option. Please choose a valid option...\n\n";
		return -1;
	}
	return result;
}

/*	Reusable function for reading raw number input from the player.
	If input contains non-digits, it will return -1 which is intepreted as invalid input. */
int PromptForNumber(string promptMessage) {
	string input;
	cout << promptMessage << "\n";
	cin >> input;
	for (size_t i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			cout << "\n\nInvalid input.\n\n";
			return -1;
		}
	}
	return stoi(input);
}

bool IsMatching(char char1, char char2, char char3) {
	return char1 == char2 && char1 == char3;
}

char* GenerateRandomSymbols(int cols, int rows, char randomSymbols[][3]) {
	for (size_t i = 0; i < cols; i++) {
		cout << "\n";
		for (size_t j = 0; j < rows; j++) {
			int random = rand() % 3;
			randomSymbols[i][j] = GameSymbols[random];
			cout << " " << randomSymbols[i][j] << " ";
		}
	}
	return *randomSymbols;
}

int GetNumMatches(int cols, int rows, char randomSymbols[][NUM_COLS]) {
	int numCorrectMatches = 0;

	// Check rows
	for (size_t i = 0; i < rows; i++) {
		if (IsMatching(randomSymbols[i][0], randomSymbols[i][1], randomSymbols[i][2])) numCorrectMatches++;
	}
	// Check columns
	for (size_t i = 0; i < cols; i++) {
		if (IsMatching(randomSymbols[0][i], randomSymbols[1][i], randomSymbols[2][i])) numCorrectMatches++;
	}
	// Check diagonals
	if (IsMatching(randomSymbols[0][0], randomSymbols[1][1], randomSymbols[2][2])) numCorrectMatches++;
	if (IsMatching(randomSymbols[0][2], randomSymbols[1][1], randomSymbols[2][0])) numCorrectMatches++;

	return numCorrectMatches;
}

int GetWinAmount(int numMatches, int betAmount) {
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

/*	Function responsible for handling the program sequence. */
void PrintStats(int *moneyWon, int *moneyInserted, bool showMoneyWon) {
	cout << "\n\nTotal money inserted: " << *moneyInserted;
	if (*moneyWon > 0 && showMoneyWon) {
		cout << "\nTotal money won: " << *moneyWon;
	}
}

/*	Function responsible for handling the program sequence. */
void Run() {

	// Initialization before the start of the game-loop.
	int moneyInserted = 0;
	int moneyWon = 0;
	bool bRunning = true;

	cout << " ~ ~ Welcome to One-armed Bandit ~ ~ ";

	while (bRunning) {
		// Prompt user to play or quit.
		int startOption = PromptForInputOption("\n\nWhat do you want to do?\n1. Play\n2. Quit", 2);
		if (startOption == 2) {
			bRunning = false;
			continue;
		}
		else if (startOption < 0) {
			continue;
		}

		PrintStats(&moneyWon, &moneyInserted, true);

		// Prompt user for amount of money to insert.
		int betOption = 0;
		int amountToInsert = 0;
		while (betOption < 1 || betOption > 4) {
			betOption = PromptForInputOption("\n\nChoose amount of money to insert: \n1. 100:-\n2. 300:-\n3. 500:-\n4. Nothing", 4);
		}

		// If user chooses to not insert money, then don't add anything to amount of money to insert.
		if (betOption != 4) {
			amountToInsert = betOption * 200 - 100;
		}
		
		// Add money to inserted money and check that inserted money are not zero.
		moneyInserted += amountToInsert;
		if (moneyInserted <= 0) {
			system("cls");
			cout << "\n\nYou have no money inserted. Please insert some money.";
			continue;
		}

		// Prompt for amount to bet.
		int betAmount = 0;
		while (betAmount <= 0) {
			PrintStats(&moneyWon, &moneyInserted, true);
			betAmount = PromptForNumber("\n\nType in the amount of money you want to bet:");
			if (betAmount == 0) {
				cout << "\n\nInvalid bet amount. Please try again...";
			}
		}

		// Check so that user has enough money for the bet.
		if (betAmount <= moneyInserted) {
			moneyInserted -= betAmount;
		}
		else {
			system("cls");
			cout << "\n\nYou can not bet more money than what you have inserted.";
			continue;
		}

		// Generate random symbols and check matches.
		char randomSymbols[NUM_COLS][NUM_ROWS];
		GenerateRandomSymbols(NUM_COLS, NUM_ROWS, randomSymbols);
		int numCorrectMatches = GetNumMatches(NUM_COLS, NUM_ROWS, randomSymbols);

		// Add price money according to number of matches.
		if (numCorrectMatches > 0) {
			int winAmount = GetWinAmount(numCorrectMatches, betAmount);
			cout << "\n\n" << numCorrectMatches << " matches! You won " << winAmount << " money!";
			moneyWon += winAmount;
		}
		else {
			cout << "\n\nNo matches. Try again.";
		}
	}
}

/*============================================================
	EXECUTION
============================================================*/
int main() {
	Run();
	return 0;
}
