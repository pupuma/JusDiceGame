#pragma once
class Bullet
{
private:
#if defined(_DEBUG_TEST)
	POINT pt;
	POINT ptSave;

#endif//
private:
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
	float fSaveAngle;

	float targetX;
	float targetY;

	float bulletX;
	float bulletY;

	bool isCollision;
private:
	int fSpeed;
	int iDamage;
private:
	RECT rcBullet;
	COLORREF color;
public:
	Bullet(COLORREF _color);
	~Bullet();
public:
	bool Init(int _x, int _y);
	bool Init(int _x, int _y, float _speedUp);

	void Update();
	void Render(HDC hdc);
public:
	void Fire();

	void Fire(RECT _rcTarget);

	void Fire(RECT _rcTarget, POINT _pt);
	void Fire(POINT _pt);


	void BulletMove(RECT _rcTarget);
	void BulletMove(POINT _ptTarget);


	void ResetPosition();
	void SetPosition(int _x ,int _y);
	void SetPosition(POINT _pt);
	void SetStartPosition(POINT _pt);
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
	int GetDamage() { return iDamage; }
	void SetDamage(int _damage) { iDamage = _damage; }
};

