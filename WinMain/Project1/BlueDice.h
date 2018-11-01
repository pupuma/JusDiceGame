#pragma once

#include "Dice.h"
class BlueDice
	: public Dice
{
private:
	float fSlow;
public:
	BlueDice();
	~BlueDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
public:
	void DiceAbility();
};

