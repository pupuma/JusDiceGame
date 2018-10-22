#pragma once

class SpaceShip;
class Enemy;

class InGameScene
	: public GameNode
{
private:
	RECT rc;
	Image* back;
private:
	SpaceShip* ship;
	Enemy* enemy;
public:
	InGameScene();
	~InGameScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

