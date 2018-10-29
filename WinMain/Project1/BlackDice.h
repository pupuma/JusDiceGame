#pragma once

#include "Dice.h"

class BlackDice 
	: public Dice
{
public:
	BlackDice();
	~BlackDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
public:
	void DiceAbility();
};

