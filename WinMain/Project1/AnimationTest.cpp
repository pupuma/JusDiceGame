#include "Game.h"
#include "AnimationTest.h"
#include "Animation.h"

AnimationTest::AnimationTest()
{
}

AnimationTest::~AnimationTest()
{
}
bool AnimationTest::Init()
{
	_camel = IMAGEMANAGER->AddFrameImage(TEXT("Camel"), TEXT("../Resource/Sprite/camel.bmp"),
		300, 267, 4, 3, true, RGB(255, 0, 255));

	_ani1 = new Animation;
	_ani1->Init(_camel);
	_ani1->SetDefPlayFrame(false, true);
	_ani1->SetFPS(1);

	int arrAni[] = { 1, 10, 2, 9, 3, 6 };
	_ani2 = new Animation;
	_ani2->Init(_camel);
	_ani2->SetPlayFrame(arrAni, 6, false);
	_ani2->SetFPS(1);

	_ani3 = new Animation;
	_ani3->Init(_camel);
	_ani3->SetPlayFrame(2, 8, false, true);
	_ani3->SetFPS(1);

	return true;
}

void AnimationTest::Release()
{
	SAFE_DELETE(_ani1);
	SAFE_DELETE(_ani2);
	SAFE_DELETE(_ani3);
}

void AnimationTest::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('Q'))
		_ani1->Start();
	if (KEYMANAGER->IsOnceKeyDown('W'))
		_ani2->Start();
	if (KEYMANAGER->IsOnceKeyDown('E'))
		_ani3->Start();

	_ani1->FrameUpdate(TIMEMANAGER->GetElapsedTime() * 10);
	_ani2->FrameUpdate(TIMEMANAGER->GetElapsedTime() * 10);
	_ani3->FrameUpdate(TIMEMANAGER->GetElapsedTime() * 10);
}

void AnimationTest::Render(HDC hdc)
{
	_camel->AniRender(hdc, 100, 100, _ani1);
	_camel->AniRender(hdc, 100, 200, _ani2);
	_camel->AniRender(hdc, 100, 300, _ani3);
}
