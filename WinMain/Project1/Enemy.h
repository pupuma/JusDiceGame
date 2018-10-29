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
	int iColorR;
	int iColorG;
	int iColorB;
	int iMoveSpeed;

private:
	POINT ptDestPos1;
	POINT ptDestPos2;
	POINT ptDestPos3;

	POINT ptCurrentPos;

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
	void EnemyAI();
	void DrawFont(HDC hdc);
	void DreaseHp(int _attackPoint);
public:
	RECT GetEnemyRect() { return rcEnemy; }
	int GetHeight() { return iNomalHeight; }
	int GetPosX() { return iStartX; }
	int GetPosY() { return iStartY; }
	int GetHp() { return iHp; }

};

