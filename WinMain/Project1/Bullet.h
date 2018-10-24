#pragma once
class Bullet
{
private:
#if defined(_DEBUG_TEST)
	POINT pt;
	POINT ptSave;
#endif//
private:
	bool isLive;
	bool isFire;

	int iStartPosX;
	int iStartPosY;

	int iPosX;
	int iPosY;

	int iWidth;
	int iHeight;

	float fAngle;

	float targetX;
	float targetY;

	float bulletX;
	float bulletY;

	bool isCollision;
private:
	float fSpeed;
private:
	RECT rcBullet;
public:
	Bullet();
	~Bullet();
public:
	bool Init(int _x, int _y);
	void Update();
	void Render(HDC hdc);
public:
	void Fire(RECT _rcTarget);
	void BulletMove();
	void ResetPosition();
	void SetPosition(int _x ,int _y);
public:
	bool IsFire() { return isFire; }
	void SetFire(bool _isFire) { isFire = _isFire; }
	
	RECT GetBulletRect() { return rcBullet; }
	
	int GetBulletCenterX() { return iPosX; }
	int GetBulletCenterY() { return iPosY; }

	int GetBulletStartX() { return iStartPosX; }
	int GetBulletStartY() { return iStartPosY; }

	bool IsCollision() { return isCollision; }
	void SetCollision(bool _isCollision) { isCollision = _isCollision; }

};

