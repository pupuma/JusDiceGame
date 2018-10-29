#include "Game.h"
#include "Bullet.h"



Bullet::Bullet(COLORREF _color)
{
	isLive = false;
	isFire = false;
	fSpeed = 5.0f;
	isCollision = false;
	fSaveAngle = 0;
	color = _color;
	iDamage = 1;
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
	DrawObject(hdc, rcBullet, 1, color, ELLIPSE);

#if defined(_DEBUG_TEST)
	DrawLine(hdc, ptSave, pt, 1, RGB(255, 0, 0));
#endif//
}

void Bullet::Fire(RECT _rcTarget)
{

	isFire = true;
	//targetX = _rcTarget.left + ((_rcTarget.right - _rcTarget.left) / 2);
	//targetY = _rcTarget.top + ((_rcTarget.bottom - _rcTarget.top) / 2);
	


}

void Bullet::Fire(RECT _rcTarget,POINT _pt)
{
	isFire = true;
	iPosX = _pt.x;
	iPosY = _pt.y;

}

void Bullet::BulletMove(RECT _rcTarget)
{

	targetX = _rcTarget.left + ((_rcTarget.right - _rcTarget.left) / 2);
	targetY = _rcTarget.top + ((_rcTarget.bottom - _rcTarget.top) / 2);

	ptSave.x = targetX;
	ptSave.y = targetY;

	bulletX = static_cast<float>(iPosX);
	bulletY = static_cast<float>(iPosY);

	fSaveAngle = fAngle;

	fAngle = UTIL::GetAngle(bulletX, bulletY,targetX, targetY);

	iPosX = iPosX + cosf(fAngle) * fSpeed;
	iPosY = iPosY + -sinf(fAngle)  * fSpeed;

	pt.x = iPosX;
	pt.y = iPosY;

	rcBullet = RectMakeCenter(pt.x, pt.y, iWidth, iHeight);
}

void Bullet::ResetPosition()
{
	rcBullet = RectMakeCenter(iStartPosX, iStartPosY, iWidth, iHeight);
	//iPosX = iStartPosX;
	//iPosY = iStartPosY;
	//isCollision = false;
}

void Bullet::SetPosition(int _x, int _y)
{
	iPosX = _x;
	iPosY = _y;
	rcBullet = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

}

void Bullet::SetPosition(POINT _pt)
{
	iPosX = _pt.x;
	iPosY = _pt.y;
}

void Bullet::SetStartPosition(POINT _pt)
{
	iStartPosX = _pt.x;
	iStartPosY = _pt.y;
}
