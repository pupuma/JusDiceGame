#pragma once

enum eEnemyType
{
	ENEMY_NONE,
	ENEMY_BOSS,
};

class Enemy
{
private:
	int iHp;
	bool isLive;
	bool activate;
private:
	int iPosX;
	int iPosY;
	int iStartX;
	int iStartY;

	int iNomalWidth;
	int iNomalHeight;
	int iBossWidth;
	int iBossHeight;
	int iColorR;
	int iColorG;
	int iColorB;
	float fMoveSpeed;
	float fMaxMoveSpeed;

	float fAngle;
private:
	float fFreezTime;
	float fPoisonTime;

	float fFreezDeltaTime;
	float fPoisonDeltaTime;

	bool isSlow;
	bool isPoison;
	bool isDieState;
private:
	std::queue<eStateAbnormal> q_stateAb;
private:
	POINT ptDestPos1;
	POINT ptDestPos2;
	POINT ptDestPos3;

	POINT ptCurrentPos;

private:
	RECT rcEnemy;
	eEnemyType enemyType;
	eStateAbnormal sa;
private:
	TimeCheck* test;
public:
	Enemy();
	~Enemy();
public:
	bool Init();
	bool Init(int _y);
	void Update();
	void Render(HDC hdc);
public:
	void EnemyAI();
	void DrawFont(HDC hdc);
	void DreaseHp(int _attackPoint);
	void StateAbnormalEffect(int _posX, int _posY);
	void Poison(int _posX, int _posY);
	void Slow(int _posX, int _posY);
	
public:
	RECT GetEnemyRect() { return rcEnemy; }
	int GetHeight() { return iNomalHeight; }
	int GetPosX() { return iStartX; }
	int GetPosY() { return iStartY; }
	int GetHp() { return iHp; }
	void SetStateAbnormalEffect(eStateAbnormal _sa) { sa = _sa; }
	bool IsLive() { return isLive; }
	void SetLive(bool _isLive) { isLive = _isLive; }
	bool GetActivate() { return activate; }
	void SetActivate(bool act) { activate = act; }

};

