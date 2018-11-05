#pragma once

#include "SingletonBase.h"

class DiceManager
	: public SingletonBase<DiceManager>
{
private:
	int iRedPrice;
	int iYellowPrice;
	int iBluePrice;
	int iGreenPrice;
	int iBlackPrice;
	int iGrayPrice;

	int iRedLevel;
	int iYellowLevel;
	int iBlueLevel;
	int iGreenLevel;
	int iBlackLevel;
	int iGrayLevel;

	int iRedDamage;
	int iYellowDamage;
	int iBlueDamage;
	int iGreenDamage;
	int iBlackDamage;
	int iGrayDamage;

	int iRedEffectPower;
	int iYellowEffectPower;
	int iBlueEffectPower;
	int iGreenEffectPower;
	int iBlackEffectPower;
	int iGrayEffectPower;

public:
	DiceManager();
	~DiceManager();
public:
	//
	void SetRedDicePrice(int _redPrice) { iRedPrice = _redPrice; }
	void SetYellowDicePrice(int _yellowPrice) { iYellowPrice = _yellowPrice; }
	void SetBlueDicePrice(int _bluePrice) { iBluePrice = _bluePrice; }
	void SetGreenDicePrice(int _greenPrice) { iGreenPrice = _greenPrice; }
	void SetBlackDicePrice(int _blackPrice) { iBlackPrice = _blackPrice; }
	void SetGrayDicePrice(int _grayPrice) { iGrayPrice = _grayPrice; }

	int GetRedDicePrice() { return iRedPrice; }
	int GetYellowDicePrice() { return iYellowPrice; }
	int GetBlueDicePrice() { return iBluePrice; }
	int GetGreenDicePrice() { return iGreenPrice; }
	int GetBlackDicePrice() { return iBlackPrice; }
	int GetGrayDicePrice() { return iGrayPrice; }

	//
	void SetRedDiceLevel(int _redLevel) { iRedLevel = _redLevel; }
	void SetYellowDiceLevel(int _yellowLevel) { iYellowLevel = _yellowLevel; }
	void SetBlueDiceLevel(int _blueLevel) { iBlueLevel = _blueLevel; }
	void SetGreenDiceLevel(int _greenLevel) { iGreenLevel = _greenLevel; }
	void SetBlackDiceLevel(int _blackLevel) { iBlackLevel = _blackLevel; }
	void SetGrayDiceLevel(int _grayLevel) { iGrayLevel = _grayLevel; }

	int GetRedDiceLevel() { return iRedLevel; }
	int GetYellowDiceLevel() { return iYellowLevel; }
	int GetBlueDiceLevel() { return iBlueLevel; }
	int GetGreenDiceLevel() { return iGreenLevel; }
	int GetBlackDiceLevel() { return iBlackLevel; }
	int GetGrayDiceLevel() { return iGrayLevel; }


	//
	void SetRedDiceDamage(int _redDamage) { iRedDamage = _redDamage; }
	void SetYellowDiceDamage(int _yellowDamage) { iYellowDamage = _yellowDamage; }
	void SetBlueDiceDamage(int _blueDamage) { iBlueDamage = _blueDamage; }
	void SetGreenDiceDamage(int _greenDamage) { iGreenDamage = _greenDamage; }
	void SetBlackDiceDamage(int _blackDamage) { iBlackDamage = _blackDamage; }
	void SetGrayDiceDamage(int _grayDamage) { iGrayDamage = _grayDamage; }

	int GetRedDiceDamage() { return iRedDamage; }
	int GetYellowDiceDamage() { return iYellowDamage; }
	int GetBlueDiceDamage() { return iBlueDamage; }
	int GetGreenDiceDamage() { return iGreenDamage; }
	int GetBlackDiceDamage() { return iBlackDamage; }
	int GetGrayDiceDamage() { return iGrayDamage; }

	//
	void SetRedDiceEffectPower(int _redEffectPower) { iRedEffectPower = _redEffectPower; }
	void SetYellowDiceEffectPower(int _yellowEffectPower) { iYellowEffectPower = _yellowEffectPower; }
	void SetBlueDiceEffectPower(int _blueEffectPower) { iBlueEffectPower = _blueEffectPower; }
	void SetGreenDiceEffectPower(int _greenEffectPower) { iGreenEffectPower = _greenEffectPower; }
	void SetBlackDiceEffectPower(int _blackEffectPower) { iBlackEffectPower = _blackEffectPower; }
	void SetGrayDiceEffectPower(int _grayEffectPower) { iGrayEffectPower = _grayEffectPower; }

	int GetRedDiceEffectPower() { return iRedEffectPower; }
	int GetYellowDiceEffectPower() { return iYellowEffectPower; }
	int GetBlueDiceEffectPower() { return iBlueEffectPower; }
	int GetGreenDiceEffectPower() { return iGreenEffectPower; }
	int GetBlackDiceEffectPower() { return iBlackEffectPower; }
	int GetGrayDiceEffectPower() { return iGrayEffectPower; }

	//
public:
	void Reset();
};

