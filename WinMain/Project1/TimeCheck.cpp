#include "Game.h"
#include "TimeCheck.h"



TimeCheck::TimeCheck(const TCHAR* str)
{
	iDeltaTime = GetTickCount();
	
	strText = str;


	TCHAR tDelta[256];
	_stprintf(tDelta, TEXT("���� �ð� : %d"), iDeltaTime);
	deltaText = tDelta;

}


TimeCheck::~TimeCheck()
{
	TCHAR tEnd[256];
	iEndTime = GetTickCount();

	_stprintf(tEnd, TEXT("�ص� �ð� : %d , ���� : %d "), iEndTime, (iEndTime - iDeltaTime));
	endTest = tEnd;

	OutputDebugString(strText.c_str());
	OutputDebugString(deltaText.c_str());
	OutputDebugString(endTest.c_str());
	OutputDebugString(TEXT("\n"));



}
