#pragma once

#define MAXBULLET 6

class Bullet;
class State;

enum eDiceColor
{
	DICE_NONE,
	DICE_BLUE,
	DICE_RED,
	DICE_GREEN,
	DICE_YELLOW,
	DICE_GRAY,
	DICE_BLACK,
};

class Dice
{
private:
	eStateType stateType;
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
	//Bullet* bullet[MAXBULLET];
	std::vector<Bullet*> bulletList;
	std::vector<Bullet*>::iterator it;
private:
	eDiceColor diceType;
	tagLevelPosition levelPos;
private:
	Image* _image;
	POINT ptDiceCenterPos;
	POINT ptDicePos;
	POINT ptSave;
private:
	RECT rcDice;
	RECT rcGameBoard;
	//RECT targetRect;
	RECT rcTarget;
private:
	int iDiceStartX;
	int iDiceStartY;
	
	int iDiceWidth;
	int iDiceHeight;
	
	int iLevel;
	int iIndex;

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
	bool Init(int _x, int _y, RECT _rcGameBoard, eDiceColor _color);

	void Update();
	void Render(HDC hdc);
public:
	void DiceLevelBullet(int _level, int _x , int _y);
	void DiceLevelBulletUpdate(int _level, int _x, int _y);

	void LevelDiceRender(HDC hdc);
	POINT DiceStartFirePos(int _level, int _x, int _y);
	void DiceFirePos(int _level, int _x, int _y);
	void SetColor(eDiceColor _color);


	
public:
	int GetDiceLevel() { return iLevel; }
	bool IsClick() { return isClick; }
	
	void SetClick(bool _click) { isClick = _click; }
	RECT GetRectDice() { return rcDice; }
	
	void SetDicePosition(POINT _pt) { ptDiceCenterPos = _pt; }
	POINT GetDiceCenterPosition() { return ptDiceCenterPos; }

	std::vector<Bullet*> GetBulletList() { return bulletList; }

};

