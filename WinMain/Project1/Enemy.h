#pragma once

enum eEnemyType
{
	ENEMY_NONE,
	ENEMY_BOSS,
};

class Enemy
{
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
	void Update();
	void Render(HDC hdc);
public:
	RECT GetEnemyRect() { return rcEnemy; }

};

