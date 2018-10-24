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
		return true;
	}

	return false;
	
}



void GameSystem::AddEnemy()
{
}

int GameSystem::EnemyType()
{
	
	/*
	일반몹 스테이지  =  iRound * iCount ; 
	보스몹 스테이지 =  iRound * iCount * iBossConstant;
	
	*/
	iRound = iRound * iCount;

	return iRound;
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
