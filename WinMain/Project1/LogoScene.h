#pragma once
class LogoScene
	: public GameNode
{
private:
	Image* img;
	float fDeltaTime;
public:
	LogoScene();
	~LogoScene();
public:
	bool Init();
	void Update();
	void Render(HDC hdc );

};

