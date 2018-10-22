#include "Game.h"
#include "GameSystem.h"

#include "Player.h"	

#include "Monster.h"


GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
}


void GameSystem::SetMonster(Monster* monster)
{
	_monster = monster;
}

void GameSystem::CrashCharacter(Player* player)
{
	RECT rcPlayer = player->GetRectPlayer();
	RECT rcMonster = _monster->GetRectMonster();
	RECT rcTemp;
	if (IntersectRect(&rcTemp, &rcPlayer, &rcMonster))
	{
		if (rcPlayer.right <= rcMonster.left + (rcMonster.right - rcMonster.left) / 2)
		{
			player->CrashObject(0);
		}
		else
		{
			player->CrashObject(1);
		}
	}
}

void GameSystem::SetMousePosition(LPARAM lParam)
{
	_ptMouse.x = LOWORD(lParam);
	_ptMouse.y = HIWORD(lParam);
}


POINT GameSystem::GetMousePosition()
{
	return _ptMouse;
}