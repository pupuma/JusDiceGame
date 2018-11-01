#pragma once

class Bullet;
class Enemy;
class Dice;

typedef std::map<std::string, HFONT> MFONT;

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
	int iMaxSpeed;

	float fSpeedUp;
	float fSpeed;
	bool isEnemyActivate;
	float fCircleRadius;
	bool isFire;
	int chainCount;
	
private:
	float slowPoint;
	int poisonDamge;
	int iProbabilitySize;
	int attackPoint;
	POINT ptSave;
	POINT ptLineFirst;
	POINT ptLineSecend;
private:
	RECT rcGameBoard;
	RECT rc;
private:
	std::list<std::pair<int,Enemy*>> enemyList;
	std::list<std::pair<int,Enemy*>>::iterator it_Enemy;

	std::vector<Dice*> diceList;
	std::vector<int> randomList;

	std::vector<std::pair<bool, POINT>> g_DiceSaveInfo;
	std::list<std::pair<int, Dice*>> g_DiceList;
	std::list<std::pair<int, Dice*>>::iterator it_Dice;


	std::vector<std::pair<bool, POINT>> pSaveInfo;
	std::pair<bool, POINT> saveDiceInfo;
	std::pair<int, Dice*> diceInfo;
	std::vector<POINT> gameLineList;
	std::queue<std::pair<int, Enemy*>> q_Enemy;
	//POINT ptSaveDice[GAMEBOARDSIZE];

private:
	float fCoolTime;
	float fDeltaTime;
	MFONT				fontMap;
	MFONT::iterator		it_Font;
	Dice* _dice;
public:
	GameSystem();
	~GameSystem();
public:
	bool Init();
public:
	void EnemyUpdate();
	void EnemyListRender(HDC hdc);

	//void CollisionBullet(Dice* _dice, int _index, std::pair<int, RECT> _pData);
	void CollisionBullet(Dice* _dice, int _index, std::pair<int, POINT> _pData);

	void CollisionObject(std::list<Enemy*> enemyList);
	void BulletCollision();

	void AddEnemy(Enemy* _enemy, int index);

	int EnemyType();
	int EnemyCount();

	//std::pair<int, RECT> GetRectEnemy(Dice* dice);
	std::pair<int, POINT> GetPosEnemy(Dice* dice);

	int GetEnemyHp();
	void GetDiceList(std::vector<Dice*> _diceList);
	void AddDice();
	void RenderText(HDC hdc, const std::string fontName, const std::string strText, POINT * pos, COLORREF color);
	void TextEnemyHpRender(HDC hdc, int iHp, RECT* rc, COLORREF color);
	Dice* DiceRandomCreate(int _rand);
	std::list<std::pair<int, Dice*>> ConvergeDice(std::list<std::pair<int, Dice*>> _diceList, int _selectNumber, int _destSelectNumber, int _level);
	void SelectDeleteDice(int _number);
	void SelectAddDice(int _index, POINT _pt, int _level); 
	bool CompareDice(std::list<std::pair<int, Dice*>> _diceList, int _selectNumber, int _destSelectNumber);
	bool IsEnemyEmpty();
	bool RandomDie();
	float GetSlowPoint();
	void DiceStateAdnormal(Dice* dice);
	float GetSpeed();
	float GraySpeed();
	void SetDiceListOn(std::list<std::pair<int, Dice*>> _diceList,int iSelectNumber);
	void SetDiceListOff();
	void EnemyProDuce();
	//std::pair<int, RECT> TargetUpdate(std::pair<int, RECT> _target);
	std::pair<int, POINT> TargetUpdate(std::pair<int, POINT> _target);
	void EnemyDamage(int _index, Dice* _dice);
	void ChainRender(HDC hdc, BYTE _key);

public:
	void SetRound(int _round) { iRound = _round; }
	int GetRound() { return iRound; }

	//void SetEnemyList(std::list<Enemy*> _enemyList) { enemyList = _enemyList; }
	void SetEnemyList(std::list<std::pair<int,Enemy*>> _enemyList) { enemyList = _enemyList; }
	std::list<std::pair<int,Enemy*>> GetEnemyList() { return enemyList; }
	void SetfCoolTime(float _coolTime) { fCoolTime = _coolTime; }
	//std::vector<Dice*> GetDiceList() { return diceList; }
	void SetGameBoardInfo(std::vector<std::pair<bool, POINT>> _info) { g_DiceSaveInfo = _info; }
	void SetRectGameBoard(RECT _rc) { rcGameBoard = _rc; }

	std::list<std::pair<int, Dice*>> GetDiceList() { return g_DiceList; }
	void SetDiceList(std::list<std::pair<int, Dice*>> _diceList) { g_DiceList = _diceList; }

	void SetGameLine(std::vector<POINT> _gameLineList) { gameLineList = _gameLineList; }
	std::vector<POINT>  GetGameLine() { return gameLineList; }

	bool IsEnemyActivate() { return isEnemyActivate; }
	void SetEnemyActivate(bool _active) { isEnemyActivate = _active; }

	void SetSlowPoint(float _slow) { slowPoint = _slow; }
	
	void SetPoisonPoint(int _iDamage) { poisonDamge = _iDamage; }
	int GetPoisonPoint() { return poisonDamge; }

	void SetProbabilitySize(int _probability) { iProbabilitySize = _probability; }
	int GetProbabilitySize() { return iProbabilitySize; }

	void SetSpeedUp(float _speedUp) { fSpeedUp = _speedUp; }
	float GetSpeedUp() { return fSpeedUp; }

	int GetMaxSpeed() { return iMaxSpeed; }
	void SetSpeed(float _speed) { fSpeed = _speed; }

	void SetCircleFireRadius(float _r) { fCircleRadius = _r; }
	float GetCircleFireRadius() { return fCircleRadius; }
	
	bool IsFire() { return isFire; }
	void SetFire(bool _fire) { isFire = _fire; }
};

