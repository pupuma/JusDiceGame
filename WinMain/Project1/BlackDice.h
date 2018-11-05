#pragma once

#include "Dice.h"

class BlackDice 
	: public Dice
{
private:
	int iProbability;
public:
	BlackDice();
	~BlackDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
	void Update();
public:
	void DiceAbility();
};

