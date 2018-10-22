#include "Game.h"
#include "TrigonometricTest.h"
#include "CollisionFunction.h"


TrigonometricTest::TrigonometricTest()
{
}


TrigonometricTest::~TrigonometricTest()
{
}

bool TrigonometricTest::Init()
{
	// cannon Init
	_cannon.angle = PI / 2;
	_cannon.length = 80;
	_cannon.radius = 50;
	_cannon.center.x = WINSIZEX/2;
	_cannon.center.y = WINSIZEY;
	_cannon.end.x = _cannon.center.x;
	_cannon.end.y = _cannon.center.y;

	// Bullet Init
	for (int i = 0; i < MAX_BULLET; i++)
	{
		_bullet[i].radius = 15;
		_bullet[i].speed = 1.f;
		_bullet[i].isFire = false;
		_bullet[i].gravity = 0.0f;
		_bullet[i].iCount = 0;
	}

	// Player Init
	_player._x = WINSIZEX / 2 + 100;
	_player._y = WINSIZEY / 2;

	_player._radius = 40.0f;
	_player._angle = PI;
	_player._speed = 1.f;
	_player._gunEndX = _player._x;
	_player._gunEndY = _player._y;
	_player._gunLength = 50.f;


	return true;
}

void TrigonometricTest::Release()
{

}

void TrigonometricTest::Update()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && _cannon.angle < 3.03f)
	{
		_cannon.angle += 0.04f;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && _cannon.angle > 0.1f)
	{
		_cannon.angle -= 0.04f;
	}
	
	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		BulletFire();
	}
	BulletMove();

	BulletCollision();

	if (KEYMANAGER->IsStayKeyDown('A'))
	{
		_player._angle += 0.01;
	}
	if (KEYMANAGER->IsStayKeyDown('D'))
	{
		_player._angle -= 0.01f;
	}
	if (KEYMANAGER->IsStayKeyDown('W'))
	{
		_player._x += cosf(_player._angle) * _player._speed;
		_player._y += -sinf(_player._angle) * _player._speed;

	}
	if (KEYMANAGER->IsStayKeyDown('S'))
	{
	}

	_player._gunEndX = _player._x + cosf(_player._angle) * 50.0f;
	_player._gunEndY = _player._y + (-sinf(_player._angle)) * 50.0f;


	_cannon.end.x = _cannon.center.x + (cosf(_cannon.angle) * _cannon.length );
	_cannon.end.y = _cannon.center.y + (-sinf(_cannon.angle) * _cannon.length);
}

void TrigonometricTest::Render(HDC hdc)
{
	// Cannon Render

	EllipseMakeCenter(hdc, _cannon.center.x, _cannon.center.y,
		_cannon.radius * 2, _cannon.radius * 2);
	LineMake(hdc, _cannon.center.x, _cannon.center.y,_cannon.end.x, _cannon.end.y);

	// Bullet Render
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!_bullet[i].isFire)
		{
			continue;
		}

		EllipseMakeCenter(hdc, _bullet[i].x, _bullet[i].y,
			_bullet[i].radius * 2, _bullet[i].radius * 2);
	}

	// Player Render
	EllipseMakeCenter(hdc, _player._x, _player._y, _player._radius * 2, _player._radius * 2);
	LineMake(hdc, _player._x, _player._y, _player._gunEndX, _player._gunEndY);
}

void TrigonometricTest::BulletFire()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!_bullet[i].isFire)
		{
			_bullet[i].isFire = true;
			_bullet[i].angle = _cannon.angle;
			_bullet[i].x = _cannon.end.x;
			_bullet[i].y = _cannon.end.y;

			 //_bullet[i].x += _cannon.center.x + (cosf(_cannon.angle) * (_cannon.length + 10));
			 //_bullet[i].y += _cannon.center.y + (-sinf(_cannon.angle) * (_cannon.length + 10));

			break;
		}
	}
}

void TrigonometricTest::BulletMove()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (_bullet[i].isFire)
		{
			_bullet[i].x += cosf(_bullet[i].angle) * _bullet[i].speed;
			_bullet[i].y += -sinf(_bullet[i].angle) * _bullet[i].speed;
		}
	}
	CheckCollision();
}


void TrigonometricTest::CheckCollision()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (_bullet[i].isFire)
		{
			if (_bullet[i].x <= _bullet->radius ||
				_bullet[i].x >= WINSIZEX - _bullet->radius)
			{
				_bullet[i].angle = PI - _bullet[i].angle;
				_bullet[i].iCount++;
			}
			else if (_bullet[i].y <= _bullet->radius ||
				_bullet[i].y >= WINSIZEY - _bullet->radius)
			{
				_bullet[i].angle = PI2 - _bullet[i].angle;
				_bullet[i].iCount++;
			}

		/*	if (CollisionCircleAndCircle(_bullet[i].radius, _bullet[i].x, _cannon.center.x,
				_cannon.radius, _bullet[i].y, _cannon.center.y))
			{
				_bullet[i].isFire = false;

			}*/


			if (_bullet[i].iCount > 3)
			{
				_bullet[i].isFire = false;
				_bullet[i].iCount = 0;
				//_bullet[i].x = _cannon.end.x;
				//_bullet[i].y = _cannon.end.y ;
			}
		}
		
	}
}

void TrigonometricTest::BulletCollision()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		for (int j = i + 1; j < MAX_BULLET; j++)
		{
			if (_bullet[i].isFire && _bullet[j].isFire)
			{
				if (_bullet[i].radius * 2 < UTIL::GetDistance(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y))
				{
					continue;
				}
				
				_bullet[i].angle = UTIL::GetAngle(_bullet[j].x, _bullet[j].y, _bullet[i].x, _bullet[i].y);
				_bullet[j].angle = UTIL::GetAngle(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y);
			}
		}
	}
}
