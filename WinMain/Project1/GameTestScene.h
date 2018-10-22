#pragma once
class GameTestScene
	: public GameNode
{
public:
	GameTestScene();
	~GameTestScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

