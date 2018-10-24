#pragma once

class GameBoard;
class Enemy;

class GameScene
	: public GameNode
{
private:
	GameBoard* gameBoard;
	Enemy* enemy;
	std::list<Enemy*> enemyList;
	std::list<Enemy*>::iterator it;

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

public:
	GameScene();
	~GameScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};
