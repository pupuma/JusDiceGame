#pragma once
class Bullet
{
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
public:
	bool IsFire() { return isFire; }
	void SetFire(bool _isFire) { isFire = _isFire; }
	RECT GetBulletRect() { return rcBullet; }
	int GetBulletCenterX() { return iPosX; }
	int GetBulletCenterY() { return iPosY; }


public:
};

