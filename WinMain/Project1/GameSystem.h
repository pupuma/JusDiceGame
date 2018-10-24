#pragma once

class Bullet;
class Enemy;
class Dice;

class GameSystem
	: public SingletonBase<GameSystem>
{
public:
	int iRound;
	
public:
	GameSystem();
	~GameSystem();
public:
	bool CollisionBullet(Bullet* _bullet, const RECT _target);


	void AddEnemy();
public:
	void SetRound(int _round) { iRound = _round; }
	int GetRound() { return iRound; }


public:

};

