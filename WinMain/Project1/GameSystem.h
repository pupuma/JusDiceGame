#pragma once

class Bullet;
class Enemy;
class Dice;

class GameSystem
	: public SingletonBase<GameSystem>
{
public:
	int iRound;
	int iCount;
	int iBossConstant;
	
	std::list<Enemy*> enemyList;
	float fCoolTime;

public:
	GameSystem();
	~GameSystem();
public:
	bool CollisionBullet(Bullet* _bullet, const RECT _target);

	void AddEnemy();
	int EnemyType();
	int EnemyCount();
	RECT GetRectEnemy();
public:
	void SetRound(int _round) { iRound = _round; }
	int GetRound() { return iRound; }

	void SetEnemyList(std::list<Enemy*> _enemyList) { enemyList = _enemyList; }
	std::list<Enemy*> GetEnemyList() { return enemyList; }
	void SetfCoolTime(float _coolTime) { fCoolTime = _coolTime; }

};

