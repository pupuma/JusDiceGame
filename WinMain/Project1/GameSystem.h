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

	bool isEnemyActivate;
private:
	RECT rcGameBoard;
private:
	std::list<Enemy*> enemyList;
	std::list<Enemy*>::iterator it_Enemy;

	std::vector<Dice*> diceList;

	std::vector<std::pair<bool, POINT>> g_DiceSaveInfo;
	std::list<std::pair<int, Dice*>> g_DiceList;
	std::list<std::pair<int, Dice*>>::iterator it_Dice;


	std::vector<std::pair<bool, POINT>> pSaveInfo;
	std::pair<bool, POINT> saveDiceInfo;
	std::pair<int, Dice*> diceInfo;
	std::vector<POINT> gameLineList;

	//POINT ptSaveDice[GAMEBOARDSIZE];

private:
	float fCoolTime;
	MFONT				fontMap;
	MFONT::iterator		it_Font;
	Dice* _dice;
public:
	GameSystem();
	~GameSystem();
public:
	bool Init();
public:
	bool CollisionBullet(Bullet* _bullet, const RECT _target);
	void CollisionObject(std::list<Enemy*> enemyList);
	void BulletCollision();

	void AddEnemy();
	int EnemyType();
	int EnemyCount();
	RECT GetRectEnemy();
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
	void SetDiceList(std::list<std::pair<int, Dice*>> _diceList) { g_DiceList = _diceList; }

	void SetGameLine(std::vector<POINT> _gameLineList) { gameLineList = _gameLineList; }
	std::vector<POINT>  GetGameLine() { return gameLineList; }

	bool IsEnemyActivate() { return isEnemyActivate; }
	void SetEnemyActivate(bool _active) { isEnemyActivate = _active; }
	
};

