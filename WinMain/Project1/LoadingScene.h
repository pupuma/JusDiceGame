#pragma once

class ProgressBar;


class LoadingScene
	: public GameNode
{
private:
	ProgressBar*		 _loadingBar;
	Image*				 _bg;
public:
	int					 _curCount;
public:
	LoadingScene();
	~LoadingScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

static DWORD CALLBACK ThreadFunction(LPVOID lpParam);