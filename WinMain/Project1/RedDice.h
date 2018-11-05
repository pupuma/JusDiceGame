#pragma once

#include "Dice.h"

class RedDice 
	: public Dice
{
private:
	RECT rcCircleFire;
	Image* circleImg;
	Image* bulletRedImg;
private:
	int r;
	float fDeltaTime;
	float fCurrentTime;
	bool isFire;
	POINT pt;
	BYTE colorKey;

public:
	RedDice();
	~RedDice();
public:
	bool Init(int _x, int _y, RECT _rcGameBoard);
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void CircleRender(HDC hdc);
	void DiceAbility();
public:
	bool IsFire() { return isFire; }
	void SetFire(bool _fire) { isFire = _fire; }

};

