#pragma once

#include "Dice.h"
class YellowDice
	: public Dice
{
private:
	std::list<POINT> chainList;
	int chainCount;
public:
	YellowDice();
	~YellowDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);

public:
	void DiceAbility();
public:

};

