#pragma once

#include "Dice.h"

class RedDice 
	: public Dice
{
public:
	RedDice();
	~RedDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
public:
	void DiceAbility();
};

