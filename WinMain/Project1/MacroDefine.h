#pragma once

// 사용자 정의 빌드 구분 
//#define _RENDER_TEST
//#define _CROP_TEST
//#define _FRAME_TEST
//#define _TRIFUNC_TEST
//#define _STALKER_TEST
//#define _ANI_TEST
//#define _CAMERA_TEST
//#define _PIXEL_TEST
//#define _EFFECT_TEST
#define _DEBUG_TEST

#if defined(_UNICODE)
typedef  std::wstring		tstring;  //std::basic_string<wchar>
#else	
typedef  std::string		tstring;   //std::basic_string<char>
#endif // #if defined(_UNICODE)



//
#define PI				3.141592654f
#define PI2				PI*2
#define COLOR_M			RGB(255,0,255)


// 메모리 해제 매크로
#define SAFE_DELETE(p)	{if(p) {delete (p); (p) = NULL;}}
#define SAFE_RELEASE(p)	{if(p) {(p)->Release(); (p) = NULL;}}

// 윈도우 사이즈 관련 매크로
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define WINSIZEX	600
#define WINSIZEY	800
#define WINSTARTX	100
#define WINSTARTY	100


// 싱글턴 객체 매크로

#define RAND			RandomFunction::GetSingleton()
#define CAMERA			Camera::GetSingleton()
#define KEYMANAGER		KeyManager::GetSingleton()
#define TIMEMANAGER		TimeManager::GetSingleton()
#define IMAGEMANAGER	ImageManager::GetSingleton()
#define EFFECTMANAGER	EffectManager::GetSingleton()
#define SCENEMANAGER	SceneManager::GetSingleton()
#define SOUNDMANAGER	SoundManager::GetSingleton()
#define GAMESYS			GameSystem::GetSingleton()
#define STATEMANAGER	StateManager::GetSingleton()