#pragma once

#define MAXBULLET 6

class Bullet;

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
	Bullet* bullet[MAXBULLET];
private:
	eDiceColor diceType;
	tagLevelPosition levelPos;
private:
	Image* _image;
	POINT ptDiceCenterPos;
	POINT ptDicePos;
private:
	RECT rcDice;
	RECT rcGameBoard;
	RECT targetRect;
private:
	int iDiceStartX;
	int iDiceStartY;
	
	int iDiceWidth;
	int iDiceHeight;
	
	int iLevel;

	float fCoolTime;
private:
	bool isClick;
public:
	Dice();
	~Dice();
public:
	bool Init();
	bool Init(int _x, int _y);
	bool Init(int _x, int _y, RECT _rcGameBoard);
	void Update();
	void Render(HDC hdc);
public:
	void DiceLevelBullet(int _level, int _x , int _y);
	void DiceLevelBulletUpdate(int _level, int _x, int _y);

	void LevelDiceRender(HDC hdc);
public:
	int GetDiceLevel() { return iLevel; }
	bool IsClick() { return isClick; }
	
	void SetClick(bool _click) { isClick = _click; }
	RECT GetRectDice() { return rcDice; }
	
	void SetDicePosition(POINT _pt) { ptDiceCenterPos = _pt; }
	POINT GetDiceCenterPosition() { return ptDiceCenterPos; }

};

