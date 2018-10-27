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

	int iDiceWidth;
	int iDiceHeight;
	int iPrevIndex;
	int iDiceIndex;
	int iBoardCount;
private:
	RECT rcGameBoard;
private:
	std::list<Enemy*> enemyList;
	std::vector<Dice*> diceList;

	std::vector<std::pair<bool, POINT>> g_DiceSaveInfo;
	std::list<std::pair<int, Dice*>> g_DiceList;
	std::vector<std::pair<bool, POINT>> pSaveInfo;
	std::pair<bool, POINT> saveDiceInfo;
	std::pair<int, Dice*> diceInfo;
	//POINT ptSaveDice[GAMEBOARDSIZE];

private:
	float fCoolTime;

public:
	GameSystem();
	~GameSystem();
public:
	bool Init();
public:
	bool CollisionBullet(Bullet* _bullet, const RECT _target);

	void AddEnemy();
	int EnemyType();
	int EnemyCount();
	RECT GetRectEnemy();
	int GetEnemyHp();
	void GetDiceList(std::vector<Dice*> _diceList);
	void CollisionEnemy(std::list<Enemy*> _enmeyList);
	void AddDice();
public:
	void SetRound(int _round) { iRound = _round; }
	int GetRound() { return iRound; }

	void SetEnemyList(std::list<Enemy*> _enemyList) { enemyList = _enemyList; }
	std::list<Enemy*> GetEnemyList() { return enemyList; }
	void SetfCoolTime(float _coolTime) { fCoolTime = _coolTime; }
	//std::vector<Dice*> GetDiceList() { return diceList; }
	void SetGameBoardInfo(std::vector<std::pair<bool, POINT>> _info) { g_DiceSaveInfo = _info; }
	void SetRectGameBoard(RECT _rc) { rcGameBoard = _rc; }

	std::list<std::pair<int, Dice*>> GetDiceList() { return g_DiceList; }
};

