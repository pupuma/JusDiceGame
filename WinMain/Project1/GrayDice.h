#pragma once

#include "Dice.h"

class GrayDice
	: public Dice
{
private:
	int fSpeedUp;
public:
	GrayDice();
	~GrayDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
	void Update();
public:
	void DiceAbility();
	

};

