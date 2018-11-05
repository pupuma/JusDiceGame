#include "DiceManager.h"



DiceManager::DiceManager()
{
	iRedPrice = 100;
	iYellowPrice = 100;
	iBluePrice = 100;
	iGreenPrice = 100;
	iBlackPrice = 100;
	iGrayPrice = 100;

	iRedLevel = 1;
	iYellowLevel = 1;
	iBlueLevel = 1;
	iGreenLevel = 1;
	iBlackLevel = 1;
	iGrayLevel = 1;

	iRedDamage = 1;
	iYellowDamage = 1;
	iBlueDamage = 1;
	iGreenDamage = 1;
	iBlackDamage = 1;
	iGrayDamage = 1;

	iRedEffectPower = 50;
	iYellowEffectPower = 2;
	iBlueEffectPower = 1;
	iGreenEffectPower = 1;
	iBlackEffectPower = 1;
	iGrayEffectPower = 2;
}


DiceManager::~DiceManager()
{
}

void DiceManager::Reset()
{
	iRedPrice = 100;
	iYellowPrice = 100;
	iBluePrice = 100;
	iGreenPrice = 100;
	iBlackPrice = 100;
	iGrayPrice = 100;

	iRedLevel = 1;
	iYellowLevel = 1;
	iBlueLevel = 1;
	iGreenLevel = 1;
	iBlackLevel = 1;
	iGrayLevel = 1;

	iRedDamage = 1;
	iYellowDamage = 1;
	iBlueDamage = 1;
	iGreenDamage = 1;
	iBlackDamage = 1;
	iGrayDamage = 1;

	iRedEffectPower = 50;
	iYellowEffectPower = 2;
	iBlueEffectPower = 1;
	iGreenEffectPower = 1;
	iBlackEffectPower = 1;
	iGrayEffectPower = 2;
}
