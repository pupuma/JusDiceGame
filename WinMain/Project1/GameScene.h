#pragma once

class GameBoard;
class Enemy;
class DiceCreateButton;
class GameStateButton;
class DiceFuctionUI;

class GameScene
	: public GameNode
{
private:
	eGState state;
private:
	
	GameBoard* gameBoard;
	Enemy* enemy;
	DiceCreateButton* dcButtom;
	GameStateButton* gsButtom;
	DiceFuctionUI* diceUI;

	std::list<std::pair<int, Enemy*>> enemyList;
	std::list<std::pair<int, Enemy*>>::iterator it;
private:
	POINT ptGameLine1;
	POINT ptGameLine2;
	POINT ptGameLine3;
	POINT ptGameLine4;

private:
	Image* backGroundImg;
	Image* stopImgBack;

	RECT testRect;
	RECT testRect2;
	POINT ptRound;
	POINT ptRound2;
	POINT ptGold;
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
	int iEnemyCount;
	int iGold;
public:
	GameScene();
	~GameScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void DrawFont(HDC hdc);
};

