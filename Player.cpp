#include "Player.h"

int Player::GetMoney()
{
	return Money;
}

void Player::AddMoney(int amount)
{
	// Adds money to the players available money.
	Money = Money + amount < 0 ? 0 : Money + amount;
}