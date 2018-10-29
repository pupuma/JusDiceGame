#include "Game.h"
#include "YellowDice.h"

#include "Bullet.h"


YellowDice::YellowDice()
{
	diceType = eDiceColor::DICE_YELLOW;
	color = RGB(249,200,0);

}


YellowDice::~YellowDice()
{
}

bool YellowDice::Init(int _x, int _y, RECT _rcGameBoard)
{
	{
		rcGameBoard = _rcGameBoard;
		_image = new Image();

		//_image = IMAGEMANAGER->FindImage(TEXT("TestDice"));
		_image->Init(TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);
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


		// 이미지 색 
		//diceType = _color;
		_image->SetFrameX((diceType));

	}

	// 총알 위치 -> 
	{
		ptDicePos.x = _x - iDiceWidth / 2;
		ptDicePos.y = _y - iDiceHeight / 2;

		DiceLevelBullet(GetDiceLevel(), ptDicePos.x, ptDicePos.y);
	}


	return true;
}

void YellowDice::DiceAbility()
{

}
