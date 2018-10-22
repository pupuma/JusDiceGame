#pragma once

enum eDiceColor
{
	DICE_NONE,
	DICE_RED,
	DICE_YELLOW,
	DICE_BLUE,
	DICE_GREEN,
	DICE_BLACK,
	DICE_GRAY,
};

class Dice
{
private:
	eDiceColor diceType;
private:
	Image* _image;
	POINT ptDiceCenterPos;
private:
	int iDiceStartX;
	int iDiceStartY;
	int iDiceWidth;
	int iDiceHeight;
public:
	Dice();
	~Dice();
public:
	bool Init();
	void Render(HDC hdc);
};

