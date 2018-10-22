#pragma once
class EffectTest
	: public GameNode
{
private:

public:
	EffectTest();
	~EffectTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

