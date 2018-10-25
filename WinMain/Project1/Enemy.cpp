#include "Game.h"
#include "Enemy.h"



Enemy::Enemy()
{
	
	// hp
	iHp = 1;

	// position 
	iStartX = 59;
	iStartY = 60;
	
	// size
	iNomalWidth = 54;
	iNomalHeight = 44;


}


Enemy::~Enemy()
{
}

bool Enemy::Init()
{
	//
	{
		enemyType = (eEnemyType)GAMESYS->EnemyType();
	}

	{
		rcEnemy = RectMakeCenter(iStartX, iStartY, iNomalWidth, iNomalHeight);
	}
	return true;
}

bool Enemy::Init(int _y)
{
	//
	{
		enemyType = (eEnemyType)GAMESYS->EnemyType();
	}

	{
		iStartY += _y;
		rcEnemy = RectMakeCenter(iStartX, iStartY, iNomalWidth, iNomalHeight);
	}
	return true;
}

void Enemy::Update()
{
	
	{
		iStartY++;
		rcEnemy = RectMakeCenter(iStartX, iStartY, iNomalWidth, iNomalHeight);
	}
}

void Enemy::Render(HDC hdc)
{
	DrawObject(hdc, rcEnemy, 1, RGB(123, 23, 5), ROUNDRECT);
}

