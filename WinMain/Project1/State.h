#pragma once
class State
{
public:
	State();
	~State();
public:
	virtual void Start();
	virtual void Stop() {}
	virtual void Update();
	virtual void Render();

	virtual void Release();
	virtual void Reset();
};

