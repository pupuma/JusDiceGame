#pragma once

class GameBoard;
class Enemy;
class DiceCreateButton;

enum eGameType
{
	GMAE_IDLE,
	GMAE_PLAY,
	GAME_STOP,
};

class GameScene
	: public GameNode
{
private:
	GameBoard* gameBoard;
	Enemy* enemy;
	DiceCreateButton* dcButtom;

	std::list<std::pair<int, Enemy*>> enemyList;
	std::list<std::pair<int, Enemy*>>::iterator it;
	eGameType _type;
private:
	POINT ptGameLine1;
	POINT ptGameLine2;
	POINT ptGameLine3;
	POINT ptGameLine4;

private:
	Image* backGroundImg;
	RECT testRect;
	RECT testRect2;

private:
	int iStartX;
	int iStartY;
private:
	int iEnemyStartX;
	int iEnemyStartY;
private:
	float fDeltaTime;
	int iCount;
	int iRound;
public:
	GameScene();
	~GameScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

static DWORD CALLBACK ThreadFunction(LPVOID lpParam);
