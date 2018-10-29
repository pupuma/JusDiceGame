#pragma once

#include "Dice.h"

class GreenDice
	: public Dice
{
public:
	GreenDice();
	~GreenDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
public:
	void DiceAbility();
};

