#pragma once

#include "Dice.h"

class GrayDice
	: public Dice
{
public:
	GrayDice();
	~GrayDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
public:
	void DiceAbility();
};

