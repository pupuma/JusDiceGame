#pragma once

class Animation;

class Enemy
{
private:
	Image* slowImg1;
	Image* slowImg2;
	Image* slowImg3;
	Animation* slowAni1;
	Animation* slowAni2;
	Animation* slowAni3;


	Image* poisonImg1;
	Image* poisonImg2;
	Image* poisonImg3;
	Animation* poisonAni1;
	Animation* poisonAni2;
	Animation* poisonAni3;

	std::vector<Image*> slowList;
	std::vector<Image*> poisonList;

private:
	int iHp;
	bool isLive;
	bool activate;
	bool isDead;
	int iSlowCount;
	int poisonNumber;
private:
	
	int iPosX;
	int iPosY;
	int iStartX;
	int iStartY;
	int iWidth;
	int iHeight;

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
	int multiSpeed;
public:
	Enemy();
	~Enemy();
public:
	bool Init();
	bool Init(int _y ,eEnemyType _type);
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void EnemyAI();
	void DrawFont(HDC hdc);
	void DreaseHp(int _attackPoint);
	void StateAbnormalEffect(int _posX, int _posY);
	void Poison(int _posX, int _posY);
	void Slow(int _posX, int _posY);
	void SetHp(int _hp);
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
	bool IsDead() { return isDead; }

};

