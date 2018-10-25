#include "Game.h"
#include "GameSystem.h"

#include "Bullet.h"
#include "Dice.h"
#include "Enemy.h"


GameSystem::GameSystem()
{
	iRound = 1;
	iCount = 1;
	iBossConstant = 10;
	fCoolTime = 1.0f;
	iEnemyHp = 1;
}


GameSystem::~GameSystem()
{
}

bool GameSystem::CollisionBullet(Bullet* _bullet, const RECT _target)
{
	float fRadius = 7.0f;
	float fPosX = _bullet->GetBulletCenterX();
	float fPosY = _bullet->GetBulletCenterY();

	float fTargetPosX = _target.left + ((_target.right - _target.left) / 2);
	float fTargetPosY = _target.top + ((_target.bottom - _target.top) / 2);

	fCoolTime -= TIMEMANAGER->GetElapsedTime();
	if (CollisionCircleAndPoint(fRadius, fPosX, fPosY, fTargetPosX, fTargetPosY) || fCoolTime <= 0 )
	{
		_bullet->SetFire(false);
		_bullet->ResetPosition();
		_bullet->SetCollision(true);
		fCoolTime = 1.0f;

		// Enemy
		
		return true;
	}

	return false;
	
}



void GameSystem::AddEnemy()
{
}

int GameSystem::EnemyType()
{
	
	
	//iRound = iRound * iCount;
	if (0 == (iRound % 10))
	{
		return 1;
	}

	return 0;
}

int GameSystem::EnemyCount()
{
	if (0 == (iRound % 10))
	{
		return 1;
	}
	
	return iRound;
}

RECT GameSystem::GetRectEnemy()
{
	std::list<Enemy*>::iterator it =  enemyList.begin();
	RECT rc;
	//for (it = enemyList.begin(); it != enemyList.end(); it++)
	//{
	//	rc = (*it)->GetEnemyRect();
	//	break;
	//}
	rc = (*it)->GetEnemyRect();

	return rc;
}

int GameSystem::GetEnemyHp()
{

	/*
	일반몹 스테이지 별 채력  =  iRound * iCount ;
	보스몹 스테이지 별 채력  =  iRound * iCount * iBossConstant;
	*/
	if (0 == (iRound % 10))
	{
		iEnemyHp = iRound * iCount * iBossConstant;
	}
	else
	{
		iEnemyHp = iRound * iCount;
	}


	return iEnemyHp;
}

void GameSystem::GetDiceList(std::vector<Dice*> _diceList)
{
	diceList = _diceList;
}

void GameSystem::CollisionEnemy(std::list<Enemy*> _enmeyList)
{
	// Enemy
	enemyList = _enmeyList;
	std::list<Enemy*>::iterator it;

	// Dice
	//std::vector<Dice*>::iterator iter;


	// Dice 
	{

	}
}
