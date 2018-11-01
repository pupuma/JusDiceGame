#include "Game.h"
#include "GreenDice.h"

#include "Bullet.h"

GreenDice::GreenDice()
{
	diceType = eDiceColor::DICE_GREEN;
	color = RGB(0, 132, 0);
	sa = eStateAbnormal::SA_POISON;
	iPoisonDamge = 1;

}


GreenDice::~GreenDice()
{
}

bool GreenDice::Init(int _x, int _y, RECT _rcGameBoard)
{
	{
		rcGameBoard = _rcGameBoard;
		_image = new Image();

		//_image = IMAGEMANAGER->FindImage(TEXT("TestDice"));
		_image->Init(TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);

		_imageOn = new Image();
		_imageOn->Init(TEXT("../../Resource/BMP/DiceOn.bmp"), 438, 62, 6, 1, true, COLOR_M);
	}

	//Bullet Create
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			//bullet[i] = new Bullet();
			Bullet* bullet = new Bullet(color);
			bulletList.push_back(bullet);
		}

		//for (int i = 0; i < MAXBULLET; i++)
		//{
		//	bulletList[i]->Fire(targetRect);
		//}

	}
	// Init
	{
		iDiceWidth = 73;
		iDiceHeight = 60;


		ptDiceCenterPos.x = _x;
		ptDiceCenterPos.y = _y;

		rcDice = RectMakeCenter(ptDiceCenterPos.x, ptDiceCenterPos.y, iDiceWidth, iDiceHeight);


		_image->SetX(rcDice.left);
		_image->SetY(rcDice.top);


		// �̹��� �� 
		//diceType = _color;
		_image->SetFrameX((diceType));

	}

	// �Ѿ� ��ġ -> 
	{
		ptDicePos.x = _x - iDiceWidth / 2;
		ptDicePos.y = _y - iDiceHeight / 2;

		DiceLevelBullet(GetDiceLevel(), ptDicePos.x, ptDicePos.y);
	}


	return true;
}

void GreenDice::DiceAbility()
{
	GAMESYS->SetPoisonPoint(iPoisonDamge);
}