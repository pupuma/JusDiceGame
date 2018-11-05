#pragma once

#include "Dice.h"
class YellowDice
	: public Dice
{
private:
	tagChainInfo chain;
	std::vector<tagChainInfo> chainList;
	int chainCount;
	float chainTime;
public:
	YellowDice();
	~YellowDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
	void Update();
	void Render(HDC hdc);
public:
	void ChainRender(HDC hdc);
	void DiceAbility();
public:

};

