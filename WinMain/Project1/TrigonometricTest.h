#pragma once
#include "GameNode.h"

#define MAX_BULLET 20 

struct Bullet
{
	float x, y;
	float speed;
	float angle;
	float gravity;
	int radius;
	bool isFire;
	int iCount;
};

struct Cannon
{
	POINT center;		 // 포대의 중심
	POINT end;			// 포신의 끝
	float angle;		// 포신의 각도
	int radius;			// 포대의 반지름
	int length;			// 포대의 길이 
};

struct sSpere
{
	float x, y;
	float r;
};
struct Player
{
	float _x,_y;
	float _radius;
	float  _angle;
	float _speed;
	float _gunEndX;
	float _gunEndY;
	float _gunLength;

};

class TrigonometricTest
	: public GameNode
{
private:
	Cannon _cannon;
	Bullet _bullet[MAX_BULLET];

	int iIndex;
private:
	Player _player;
public:
	TrigonometricTest();
	~TrigonometricTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void BulletFire();
	void BulletMove();
	void CheckCollision();

	void BulletCollision();

};

