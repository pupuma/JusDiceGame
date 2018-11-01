#include "Game.h"
#include "CollisionFunction.h"
#include "Image.h"

bool CollisionRectAndRect(const RECT& r1, const RECT& r2)
{
	if (r1.left <= r2.right && r1.right >= r2.left)
	{
		if (r1.top <= r2.bottom && r1.bottom >= r2.top)
		{
			return true;
		}
	}

	return false;
}

bool CollisionCircleAndCircle(const float r1, const float x1, const float y1, const float r2, const float x2, const float y2)
{
	if (r1 + r2 >= UTIL::GetDistance(x1, y1, x2, y2))
		return true;

	return false;
}

bool CollisionCircleAndPoint(const float r, const float x, const float y, float ptX, float ptY)
{
	float length = UTIL::GetDistance(x, y, ptX, ptY);
	if (length <= r)
	{
		return true;
	}
	return false;
}


bool CollisionCircleAndRect(const float r, const float x, const float y, RECT & r1)
{
	if (r1.left <= x && r1.right >= x &&
		r1.top <= y && r1.bottom >= y)
	{
		RECT rcEx = {
			r1.left - r,
			r1.top - r,
			r1.right + r,
			r1.bottom + r
		};
		if (rcEx.left <= x && rcEx.right >= x &&
			rcEx.top <= y && rcEx.bottom >= y)
		{
			return true;
		}
	}
	else
	{
		if (CollisionCircleAndPoint(r, x, y, static_cast<float>(r1.left), static_cast<float>(r1.top)) ||
			CollisionCircleAndPoint(r, x, y, static_cast<float>(r1.left), static_cast<float>(r1.bottom)) ||
			CollisionCircleAndPoint(r, x, y, static_cast<float>(r1.right), static_cast<float>(r1.top)) ||
			CollisionCircleAndPoint(r, x, y, static_cast<float>(r1.right), static_cast<float>(r1.bottom)))
		{
			return true;
		}
	}
	return false;
}



int CollisionPixelAndRect(Image * _mountain, int _x, int _y, COLORREF _colorKey)
{
	return 0;
}
