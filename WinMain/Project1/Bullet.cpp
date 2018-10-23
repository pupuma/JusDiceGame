#include "Game.h"
#include "Bullet.h"



Bullet::Bullet()
{
	isLive = false;
	isFire = false;
}


Bullet::~Bullet()
{
}

bool Bullet::Init(int _x, int _y)
{
	isLive = false;
	iStartPosX = _x;
	iStartPosY = _y;

	iPosX = iStartPosX;
	iPosY = iStartPosY;

	iWidth = 14;
	iHeight = 12;

	rcBullet = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

	return true;
}

void Bullet::Update()
{

	

}

void Bullet::Render(HDC hdc)
{
	DrawObject(hdc, rcBullet, 1, RGB(123, 123, 123), ELLIPSE);
}

void Bullet::Fire(RECT _rcTarget)
{
	isFire = true;
	targetX = _rcTarget.left + ((_rcTarget.right - _rcTarget.left) / 2);
	targetY = _rcTarget.top + ((_rcTarget.bottom - _rcTarget.top) / 2);
	


}

void Bullet::BulletMove()
{

	bulletX = static_cast<float>(iPosX);
	bulletY = static_cast<float>(iPosY);

	fAngle = UTIL::GetAngle(bulletX, bulletY,targetX, targetY);

	iPosX = iPosX + cosf(fAngle) * 3.0f;
	iPosY = iPosY + -sinf(fAngle) * 3.0f;

	rcBullet = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);
}

void Bullet::ResetPosition()
{
	rcBullet = RectMakeCenter(iStartPosX, iStartPosY, iWidth, iHeight);

}