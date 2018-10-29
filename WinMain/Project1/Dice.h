#pragma once

#define MAXBULLET 6

class Bullet;
class State;

enum eDiceColor
{
	DICE_BLUE,
	DICE_RED,
	DICE_GREEN,
	DICE_YELLOW,
	DICE_GRAY,
	DICE_BLACK,
	DICE_NONE,

};

class Dice
{
protected:
	eStateType stateType;
protected:
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
protected:
	//Bullet* bullet[MAXBULLET];
	std::vector<Bullet*> bulletList;
	std::vector<Bullet*>::iterator it;
protected:
	eDiceColor diceType;
	tagLevelPosition levelPos;
protected:
	Image* _image;
	POINT ptDiceCenterPos;
	POINT ptDicePos;
	POINT ptSave;
protected:
	RECT rcDice;
	RECT rcGameBoard;
	//RECT targetRect;
	RECT rcTarget;
protected:
	int iDiceStartX;
	int iDiceStartY;
	
	int iDiceWidth;
	int iDiceHeight;
	
	int iLevel;
	int iIndex;
	int iDiceIndex;
	float fCoolTime;
	int iAttackPoint;
protected:
	bool isClick;
	bool isLive;
protected:
	COLORREF color;
public:
	Dice();
	virtual ~Dice();
public:
	bool Init();
	bool Init(int _x, int _y);
	virtual bool Init(int _x, int _y, RECT _rcGameBoard);
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

	void ResetBullet();
	void RenderBullet(HDC hdc);
	virtual void DiceAbility();

public:
	int GetDiceLevel() { return iLevel; }
	void SetDiceLevel(int _level) { iLevel = _level; }
	bool IsClick() { return isClick; }
	
	void SetClick(bool _click) { isClick = _click; }
	RECT GetRectDice() { return rcDice; }
	
	void SetDicePosition(POINT _pt) { ptDiceCenterPos = _pt; }
	POINT GetDiceCenterPosition() { return ptDiceCenterPos; }

	std::vector<Bullet*> GetBulletList() { return bulletList; }
	eDiceColor GetColor() { return diceType; }
	int GetAttackPoint() { return iAttackPoint; }
	POINT GetSavePos() { return ptSave; }
	
};