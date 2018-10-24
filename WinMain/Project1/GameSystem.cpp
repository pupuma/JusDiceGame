#include "Game.h"
#include "GameSystem.h"

#include "Bullet.h"
#include "Dice.h"
#include "Enemy.h"


GameSystem::GameSystem()
{
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


	if (CollisionCircleAndPoint(fRadius, fPosX, fPosY, fTargetPosX, fTargetPosY))
	{
		_bullet->SetFire(false);
		_bullet->ResetPosition();
		_bullet->SetCollision(true);

		return true;
	}

	return false;
	
}

void GameSystem::AddEnemy()
{
}
