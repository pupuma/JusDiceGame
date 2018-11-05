#pragma once

class Bullet;
class Enemy;
class Dice;



class GameSystem
	: public SingletonBase<GameSystem>
{
private:
	eGState g_State;
private:
	int iRound;
	int iCount;
	int iBossConstant;
	int iEnemyHp;
	int slowCount;
	int poisonNumber;
	bool isFirstStart;

	int iDiceWidth;
	int iDiceHeight;
	int iPrevIndex;
	int iDiceIndex;
	int iBoardCount;
	int iMaxSpeed;
	int iEnemyCount;
	bool isFull;
	float fSpeedUp;
	float fSpeed;
	bool isEnemyActivate;
	float fCircleRadius;
	bool isFire;
	int chainCount;
	int iGold;
	int speedUp;
private:
	float slowPoint;
	int poisonDamge;
	int iProbabilitySize;
	int attackPoint;
	POINT ptSave;
	POINT ptLineFirst;
	POINT ptLineSecend;
	tagChainInfo chain;

private:
	RECT rcGameBoard;
	RECT rc;
private:
	std::list<std::pair<int,Enemy*>> enemyList;
	std::list<std::pair<int,Enemy*>>::iterator it_Enemy;

	std::vector<Dice*> diceList;
	
	//std::list<POINT> chainList;
	std::vector<tagChainInfo> chainList;
	
	std::vector<int> randomList;

	std::vector<std::pair<bool, POINT>> g_DiceSaveInfo;
	std::list<std::pair<int, Dice*>> g_DiceList;
	std::list<std::pair<int, Dice*>>::iterator it_Dice;


	std::vector<std::pair<bool, POINT>> pSaveInfo;
	std::pair<bool, POINT> saveDiceInfo;
	std::pair<int, Dice*> diceInfo;
	std::vector<POINT> gameLineList;
	std::queue<std::pair<int, Enemy*>> q_Enemy;

private:
	float fCoolTime;
	float fDeltaTime;
	//MFONT				fontMap;
	//MFONT::iterator		it_Font;
	Dice* _dice;
public:
	GameSystem();
	~GameSystem();
public:
	bool Init();
	void Release();
	void Update(); 
public:
	void EnemyUpdate();
	void EnemyListRender(HDC hdc);

	void CollisionBullet(Dice* _dice, int _index, std::pair<int, POINT> _pData);

	void BulletCollision();

	void AddEnemy(Enemy* _enemy, int index);

	int EnemyType();
	int EnemyCount();

	std::pair<int, POINT> GetPosEnemy(Dice* dice);

	int GetEnemyHp();
	void GetDiceList(std::vector<Dice*> _diceList);
	void AddDice();
	//void RenderText(HDC hdc, const std::string fontName, const std::string strText, POINT * pos, COLORREF color);
	//void TextEnemyHpRender(HDC hdc, int iHp, RECT* rc, COLORREF color);
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
	std::pair<int, POINT> TargetUpdate(std::pair<int, POINT> _target);
	void EnemyDamage(int _index, Dice* _dice);
	void ChainDamage(int _targetNumber,  Dice* _dice);
	void DiceEffect(eDiceColor _color, Dice* _dice, int _index);
	void DiceEffect(eDiceColor _color, int x , int y);

	void SetGoldSale(int _gold);
	bool GameActivate(Dice* dice, int index);
	void IsSpeedUp();
	void IsSpeedIDle();
	void Reset();
	bool GetDiceFull();
public:
	void SetRound(int _round) { iRound = _round; }
	int GetRound() { return iRound; }

	void SetEnemyList(std::list<std::pair<int,Enemy*>> _enemyList) { enemyList = _enemyList; }
	std::list<std::pair<int,Enemy*>> GetEnemyList() { return enemyList; }
	void SetfCoolTime(float _coolTime) { fCoolTime = _coolTime; }
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

	std::vector<tagChainInfo> GetChainList(){ return chainList; }
	void SetChainList(std::vector<tagChainInfo> _chainList) { chainList = _chainList; }
	int GetSlowCount() { return slowCount; }
	int GetPoisonNumber() { return poisonNumber; }

	eGState GetGameState() { return g_State; }
	void SetGameState(eGState _state) { g_State = _state; }
	int GetEnemyCount() { return iEnemyCount; }
	void ResetEnemyCount() { iEnemyCount = 0; }
	int GetGold() { return iGold; }
	void GoldGain() { iGold += 10; }
	int GetMultiSpeed() { return speedUp; }
	void ResetRound() { iRound = 1; }
	void SetGold(int _gold) { iGold = _gold; }
	bool IsFirstStart() { return isFirstStart; }
	void SetFirstStart(bool _isFirst) { isFirstStart = _isFirst; }
	
};

