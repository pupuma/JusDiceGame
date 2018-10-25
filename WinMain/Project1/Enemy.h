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
private:
	int iPosX;
	int iPosY;
	int iStartX;
	int iStartY;

	int iNomalWidth;
	int iNomalHeight;
	int iBossWidth;
	int iBossHeight;
private:
	RECT rcEnemy;
	eEnemyType enemyType;
public:
	Enemy();
	~Enemy();
public:
	bool Init();
	bool Init(int _y);
	void Update();
	void Render(HDC hdc);
public:
	
public:
	RECT GetEnemyRect() { return rcEnemy; }
	int GetHeight() { return iNomalHeight; }

};

