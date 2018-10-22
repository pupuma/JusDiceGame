#pragma once

#include "GameNode.h"

class SKrBullet;

struct Stalker
{
	float x, y;
	float angle;
	float endX, endY;
	float length;
	float speed;
	bool isLive;
	RECT rc;
};


class StalkerTest
	: public GameNode
{
private:
	Stalker _skr1;
	Stalker _skr2;
	std::vector<Stalker*> _vSkr;
	//Stalker* _stalker;
	float _angle;
	float fPosX;
	float fPosY;
	POINT ptMouse;

private:
	//std::list<Bullet*> _bulletList;
	std::vector<SKrBullet*> _bulletList;
public:
	StalkerTest();
	~StalkerTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void CollisionSkr();
	void PlayerUpdate();
	void BulletFire();
	void BulletMove();
	void BulletCollision();

};

