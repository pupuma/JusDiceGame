#pragma once
class TimeCheck
{
private:
	unsigned int iCurrentTime;
	unsigned int iDeltaTime;
	unsigned int iEndTime;

	std::string strText;
	std::string deltaText;
	std::string endTest;
public:
	TimeCheck(const TCHAR* str);
	~TimeCheck();
};

