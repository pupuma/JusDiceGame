#pragma once

enum eEnemyType
{
	ENEMY_NONE,
	ENEMY_BOSS,
};

class Enemy
{
private:
	RECT rcEnemy;
	eEnemyType enemyType;
public:
	Enemy();
	~Enemy();
public:
	void Init();

};

