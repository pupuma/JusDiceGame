#pragma once

#include "Dice.h"
class YellowDice
	: public Dice
{
public:
	YellowDice();
	~YellowDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
public:
	void DiceAbility();
};

