#pragma once

class Bullet;
class Enemy;
class Dice;

class GameSystem
	: public SingletonBase<GameSystem>
{
private:
	int iRound;
	int iCount;
	int iBossConstant;
	int iEnemyHp;
private:
	std::list<Enemy*> enemyList;
	std::vector<Dice*> diceList;
private:
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
	int GetEnemyHp();
	void GetDiceList(std::vector<Dice*> _diceList);
	void CollisionEnemy(std::list<Enemy*> _enmeyList);

 
public:
	void SetRound(int _round) { iRound = _round; }
	int GetRound() { return iRound; }

	void SetEnemyList(std::list<Enemy*> _enemyList) { enemyList = _enemyList; }
	std::list<Enemy*> GetEnemyList() { return enemyList; }
	void SetfCoolTime(float _coolTime) { fCoolTime = _coolTime; }
	std::vector<Dice*> GetDiceList() { return diceList; }

};

