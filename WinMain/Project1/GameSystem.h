#pragma once

class Bullet;
class Enemy;

class GameSystem
	: public SingletonBase<GameSystem>
{
public:
	int iRound;
	std::list<Enemy*> enemyList;
public:
	GameSystem();
	~GameSystem();
public:
	void CollisionBullet(Bullet* _bullet, const RECT _target);
	void AddEnemy();
public:
	void SetRound(int _round) { iRound = _round; }
	int GetRound() { return iRound; }
};

