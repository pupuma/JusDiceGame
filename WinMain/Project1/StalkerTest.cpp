#include "Game.h"
#include "StalkerTest.h"
#include "CollisionFunction.h"

#include "SKrBullet.h"
#include "GameSystem.h"

StalkerTest::StalkerTest()
{
}


StalkerTest::~StalkerTest()
{
}

bool StalkerTest::Init()
{
	_skr1.angle = PI / 2;
	_skr1.x = static_cast<float>(WINSIZEX) / 2.f - 200.0f;
	_skr1.y = static_cast<float>(WINSIZEY) / 2.f;
	_skr1.endX = _skr1.x;
	_skr1.endY = _skr1.y;
	_skr1.length = 10.0f;
	_skr1.rc = RectMakeCenter(_skr1.x, _skr1.y, 50, 50);
	_skr1.speed = 4.0f;
	_skr1.isLive = true;

	//
	//_skr2.angle = PI / 2;
	//_skr2.x = static_cast<float>(WINSIZEX) / 2.f + 200.0f;
	//_skr2.y = static_cast<float>(WINSIZEY) / 2.f;
	//_skr2.rc = RectMakeCenter(_skr1.x, _skr1.y, 30, 30);
	//_skr2.speed = 4.0f;

	//

	for (int i = 0; i < 4; i++)
	{
		Stalker* _stalker = new Stalker();
		switch (i)
		{
		case 0:
			_stalker->angle = PI / 2;
			_stalker->x = 0.0f;
			_stalker->y = 0.0f;
			_stalker->rc = RectMakeCenter(_stalker->x, _stalker->y, 30, 30);
			_stalker->speed = 3.0f;
			_stalker->isLive = true;

			break;
		case 1:
			_stalker->angle = PI / 2;
			_stalker->x = static_cast<float>(WINSIZEX);
			_stalker->y = 0.0f;
			_stalker->rc = RectMakeCenter(_stalker->x, _stalker->y, 30, 30);
			_stalker->speed = 3.0f;
			_stalker->isLive = true;

			break;
		case 2:
			_stalker->angle = PI / 2;
			_stalker->x = 0.0f;
			_stalker->y = static_cast<float>(WINSIZEY);
			_stalker->rc = RectMakeCenter(_stalker->x, _stalker->y, 30, 30);
			_stalker->speed = 3.0f;
			_stalker->isLive = true;

			break;
		case 3:
			_stalker->angle = PI / 2;
			_stalker->x = static_cast<float>(WINSIZEX);
			_stalker->y = static_cast<float>(WINSIZEY);
			_stalker->rc = RectMakeCenter(_stalker->x, _stalker->y, 30, 30);
			_stalker->speed = 2.0f;
			_stalker->isLive = true;

			break;
		}
		_vSkr.push_back(_stalker);

	}


	for (int i = 0; i < 10; i++)
	{
		SKrBullet* _bullet = new SKrBullet();
		_bullet->Init(15.0f, 3.f, false);
		_bulletList.push_back(_bullet);
	}

	return true;
}

void StalkerTest::Release()
{
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(_vSkr[i]);

	}
	for (int i = 0; i < 10; i++)
	{
		SAFE_DELETE(_bulletList[i]);
	}
}

void StalkerTest::Update()
{
	PlayerUpdate();
	// 적
	//_skr2.angle = UTIL::GetAngle(_skr2.x, _skr2.y, _skr1.x, _skr1.y);
	//_skr2.x += cosf(_skr2.angle) * _skr2.speed;
	//_skr2.y += (-sinf(_skr2.angle)) * _skr2.speed;
	//_skr2.rc = RectMakeCenter(_skr2.x, _skr2.y, 30, 30);


	for (int i = 0; i < 4; i++)
	{
		if (_vSkr[i]->isLive)
		{
			_vSkr[i]->angle = UTIL::GetAngle(_vSkr[i]->x, _vSkr[i]->y, _skr1.x, _skr1.y);
			_vSkr[i]->angle = UTIL::GetAngle(_vSkr[i]->x, _vSkr[i]->y, _skr1.x, _skr1.y);

			CollisionSkr();

			_vSkr[i]->x += cosf(_vSkr[i]->angle) * _vSkr[i]->speed;
			_vSkr[i]->y += (-sinf(_vSkr[i]->angle)) * _vSkr[i]->speed;
			_vSkr[i]->rc = RectMakeCenter(_vSkr[i]->x, _vSkr[i]->y, 60, 60);
		}
	}

	BulletCollision();

}

void StalkerTest::Render(HDC hdc)
{
	EllipseMakeCenter(hdc, _skr1.x, _skr1.y,
		50, 50);
	LineMake(hdc, _skr1.x, _skr1.y, _skr1.endX, _skr1.endY);


	for (int i = 0; i < 10; i++)
	{
		if (!_bulletList[i]->IsFire())
		{
			continue;
		}

		EllipseMakeCenter(hdc, _bulletList[i]->GetPosX(), _bulletList[i]->GetPosY(),
			_bulletList[i]->GetDiameter(), _bulletList[i]->GetDiameter());
	}

	//Ellipse(hdc, _skr2.rc.left, _skr2.rc.top, _skr2.rc.right, _skr2.rc.bottom);

	for (int i = 0; i < 4; i++)
	{
		if (_vSkr[i]->isLive)
		{
			Ellipse(hdc, _vSkr[i]->rc.left, _vSkr[i]->rc.top, _vSkr[i]->rc.right, _vSkr[i]->rc.bottom);

		}
	}
}

void StalkerTest::CollisionSkr()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (_vSkr[i]->isLive)
			{
				if (CollisionCircleAndCircle(15, _vSkr[i]->x, _vSkr[i]->y,
					15,  _vSkr[j]->x, _vSkr[j]->y))
				{
					_vSkr[i]->angle = UTIL::GetAngle(_vSkr[j]->x, _vSkr[j]->y, _vSkr[i]->x, _vSkr[i]->y);
					_vSkr[j]->angle = UTIL::GetAngle(_vSkr[i]->x, _vSkr[i]->y, _vSkr[j]->x, _vSkr[j]->y);
				}
			}

		}
	}
}

void StalkerTest::PlayerUpdate()
{
	if (KEYMANAGER->IsStayKeyDown('A'))
	{
		//_skr1.angle += 0.04f;
		_skr1.x += cosf(_skr1.angle) * 1.1f;

		_skr1.x -= _skr1.speed;
	}

	if (KEYMANAGER->IsStayKeyDown('D'))
	{
		//_skr1.angle -= 0.04f;
		_skr1.x += cosf(_skr1.angle) * 1.1f;
		_skr1.x += _skr1.speed;
	}

	if (KEYMANAGER->IsStayKeyDown('W'))
	{
		_skr1.y -= _skr1.speed;
		//_skr1.speed++;
	}

	if (KEYMANAGER->IsStayKeyDown('S'))
	{
		_skr1.y += -sinf(_skr1.angle) * 1.1f;
		_skr1.y += _skr1.speed;
		//_skr1.speed--;
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		BulletFire();
	}
	BulletMove();

	//
	ptMouse = GameSystem::GetSingleton()->GetMousePosition();
	_angle = UTIL::GetAngle(_skr1.x, _skr1.y, ptMouse.x, ptMouse.y);
	//_skr1.endX = _skr1.x + cosf(_skr1.angle) * 25.0f;
	//_skr1.endY = _skr1.y + (-sinf(_skr1.angle)) * 25.0f;

	_skr1.endX = _skr1.x + cosf(_angle) * 25.0f;
	_skr1.endY = _skr1.y + (-sinf(_angle)) * 25.0f;

	_skr1.rc = RectMakeCenter(_skr1.x, _skr1.y, 60, 60);

}

void StalkerTest::BulletFire()
{

	for (int i = 0; i < 10; i++)
	{
		if (!_bulletList[i]->IsFire())
		{
			_bulletList[i]->SetFire(true);
			_bulletList[i]->SetAngle(_angle);
			_bulletList[i]->SetPosX(_skr1.endX);
			_bulletList[i]->SetPosY(_skr1.endY);

			break;
		}
	}
}

void StalkerTest::BulletMove()
{
	for (int i = 0; i < 10; i++)
	{
		if (_bulletList[i]->IsFire())
		{

			fPosX = _bulletList[i]->GetPosX() + (cosf(_bulletList[i]->GetAngle()) * _bulletList[i]->GetSpeed());
			fPosY = _bulletList[i]->GetPosY() + ((-sinf(_bulletList[i]->GetAngle())) * _bulletList[i]->GetSpeed());

			_bulletList[i]->SetPosX(fPosX);
			_bulletList[i]->SetPosY(fPosY);

		}
	}

}

void StalkerTest::BulletCollision()
{

	//
	for (int i = 0; i < 10; i++)
	{
		if (_bulletList[i]->IsFire())
		{
			if (_bulletList[i]->GetPosX() <= _bulletList[i]->GetRadius() ||
				_bulletList[i]->GetPosX() >= WINSIZEX - _bulletList[i]->GetRadius())
			{
				_bulletList[i]->SetFire(false);
				break;

			}
			 if (_bulletList[i]->GetPosY() <= _bulletList[i]->GetRadius() ||
				_bulletList[i]->GetPosY() >= WINSIZEX - _bulletList[i]->GetRadius())
			{
				_bulletList[i]->SetFire(false);
				break;
			}
		}
	}

	// 총알끼리 충돌
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (_bulletList[i]->IsFire() && _bulletList[j]->IsFire())
			{
				if (_bulletList[i]->GetRadius() * 2 < UTIL::GetDistance(_bulletList[i]->GetPosX(), _bulletList[i]->GetPosY(),
					_bulletList[j]->GetPosX(), _bulletList[j]->GetPosY()))
				{
					continue;
				}
				_bulletList[i]->SetAngle(UTIL::GetAngle(_bulletList[j]->GetPosX(), _bulletList[j]->GetPosY(),
					_bulletList[i]->GetPosX(), _bulletList[i]->GetPosY()));
				_bulletList[j]->SetAngle(UTIL::GetAngle(_bulletList[i]->GetPosX(), _bulletList[i]->GetPosY(),
					_bulletList[j]->GetPosX(), _bulletList[j]->GetPosY()));
			}
		}
	}

	// 적과의 충돌
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_vSkr[j]->isLive && _bulletList[i]->IsFire())
			{
				if (CollisionCircleAndCircle(_bulletList[i]->GetRadius(), _bulletList[i]->GetPosX(),
					_bulletList[i]->GetPosY(), 30,  _vSkr[j]->x, _vSkr[j]->y))
				{
					_vSkr[j]->isLive = false;
					_bulletList[i]->SetFire(false);
				}
			}
		}
	}
}

