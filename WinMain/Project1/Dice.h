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
	 struct tagLevelPosition
	{
		int iCircleStartX;
		int iCircleStartY;
		RECT rcLevel1;
		RECT rcLevel2[2];
		RECT rcLevel3[3];
		RECT rcLevel4[4];
		RECT rcLevel5[5];
		RECT rcLevel6[6];
	};
private:
	eDiceColor diceType;
	tagLevelPosition levelPos;
private:
	Image* _image;
	POINT ptDiceCenterPos;
	POINT ptDicePos;
private:
	int iDiceStartX;
	int iDiceStartY;
	
	int iDiceWidth;
	int iDiceHeight;
	
	

	int iLevel;

public:
	Dice();
	~Dice();
public:
	bool Init();
	bool Init(int _x, int _y);
	void Render(HDC hdc);
public:
	void DiceLevelBullet(int _level, int _x , int _y);
public:
	int GetDiceLevel() { return iLevel; }
};

