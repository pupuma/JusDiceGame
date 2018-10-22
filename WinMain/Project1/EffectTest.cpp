#include "Game.h"
#include "EffectTest.h"

//#include "Effect.h"


EffectTest::EffectTest()
{
}


EffectTest::~EffectTest()
{
}
bool EffectTest::Init()
{
	SOUNDMANAGER->Init();

	EFFECTMANAGER->AddEffect(TEXT("Effect1"), TEXT("../Resource/Sprite/effect5.bmp"), 740, 444, 148, 148, 1, 1.0f, 10);
	EFFECTMANAGER->AddEffect(TEXT("Effect2"), TEXT("../Resource/Sprite/1233.bmp"),
		360, 30, 30, 30, 5, 1.0f, 10);
	EFFECTMANAGER->AddEffect(TEXT("slow"), TEXT("../Resource/Sprite/pos.bmp"),
		270, 44, 54, 44, 5, 1.f,1);

	SOUNDMANAGER->AddSound(TEXT("Sound1"), TEXT("../Resource/Sound/SoundM/Sound/effect.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("BGS"), TEXT("../Resource/Sound/SoundM/Sound/TheConceptofLove.wav"), true, true);

	//SOUNDMANAGER->Play(TEXT("BGS"), 1.f);
	
	return true;
}

void EffectTest::Release()
{
	SOUNDMANAGER->Release();
}

void EffectTest::Update()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &(_ptMouse));

		
		//SOUNDMANAGER->Play(TEXT("Sound1"), 0.3f);


		EFFECTMANAGER->Play(TEXT("slow"), _ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &(_ptMouse));

		EFFECTMANAGER->Play(TEXT("Effect2"), _ptMouse.x, _ptMouse.y);
	}

	EFFECTMANAGER->Update();
	SOUNDMANAGER->Update();
}

void EffectTest::Render(HDC hdc)
{
	EFFECTMANAGER->Render(hdc);
}


/*
createStream�� ���� ��쿡�� Update�� �ؾ� �Ѿ� ������, 
�ٽ� ����� �Ҷ���쿡�� ���� ���� �������� ������ �Ǿ , �ٽ� ������� �ȴ�. 
createSound�� ����� �� �޸𸮸� ���� �Ѵ�. 
*/

