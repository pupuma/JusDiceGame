#pragma once

#define MAXBULLET 6

class Bullet;
class State;


class Dice
{
protected:
	eStateType stateType;
	eStateAbnormal sa;
	float radius;
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
	std::vector<Bullet*> bulletList;
	std::vector<Bullet*>::iterator it;
	std::pair<int, POINT> _target;
protected:
	eDiceColor diceType;
	tagLevelPosition levelPos;
	
protected:
	Image* _image;
	Image* _imageOn;
	POINT ptDiceCenterPos;
	POINT ptDicePos;
	POINT ptSave;
	POINT ptPrev;
protected:
	RECT rcDice;
	RECT rcGameBoard;
	RECT rcTarget;
	BYTE blackKey;
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
	bool isDiceOn;
	bool isTarget;
	bool isChain;
	float fBulletCoolTIme;
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

	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
public:
	virtual void CircleRender(HDC hdc);
	virtual void ChainRender(HDC hdc);
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
	eStateAbnormal GetStateAbnormalEffect() { return sa; }

	float GetRadius() { return radius; }

	void SetDiceOn(bool _isDiceOn) { isDiceOn = _isDiceOn; }
	void SetTargeting(bool _isTarget) { isTarget = _isTarget;}
	bool IsTargeting() { return isTarget; }
	void SetChain(bool _chain) { isChain = _chain; }
	bool IsChain() { return isChain; }
};