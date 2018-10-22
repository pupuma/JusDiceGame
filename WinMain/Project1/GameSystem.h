#pragma once

#include "SingletonBase.h"

class Monster;
class Player;

class GameSystem
	: public SingletonBase<GameSystem>
{
private:
	Monster* _monster;
	Player* _player;
public:
	GameSystem();
	~GameSystem();
public:
	void SetMonster(Monster* monster);
	void CrashCharacter(Player* player);

	void SetMousePosition(LPARAM lParam);
	POINT GetMousePosition();

};

