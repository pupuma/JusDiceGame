#include "Game.h"
#include "GameSystem.h"

#include "Bullet.h"


GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
}

void GameSystem::CollisionBullet(Bullet* _bullet, const RECT _target)
{
	float fRadius = 7.0f;
	float fPosX = _bullet->GetBulletCenterX();
	float fPosY = _bullet->GetBulletCenterY();

	float fTargetPosX = _target.left + ((_target.right - _target.left) / 2);
	float fTargetPosY = _target.top + ((_target.bottom - _target.top) / 2);


	if (CollisionCircleAndPoint(fRadius, fPosX, fPosY, fTargetPosX, fTargetPosY))
	{
		_bullet->SetFire(false);
		_bullet->ResetPosition();
	}
}

void GameSystem::AddEnemy()
{
	int round = GetRound();

	if ((round % 10) == 0)
	{
		// 보스 몬스터 생성 
	}
	else
	{
		// 일반 몬스터 생성 
	}
}
