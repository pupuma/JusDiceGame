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

	std::list<Enemy*> enemyList;
	std::list<Enemy*>::iterator it;
	eGameType _type;
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
	
public:
	GameScene();
	~GameScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void ChangeType();
};
