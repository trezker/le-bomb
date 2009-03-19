#include "interface/Rect.h"

namespace interface
{

Rect::Rect()
{}

Rect::Rect(float x, float y, float w, float h)
{
	topleft.Set(x, y);
	bottomright.Set(x+w, y+h);
}

void Rect::Set(float x, float y, float w, float h)
{
	topleft.Set(x, y);
	bottomright.Set(x+w, y+h);
}

Vector2 Rect::Topleft()
{
	return topleft;
}

Vector2 Rect::Bottomright()
{
	return bottomright;
}

Vector2 Rect::Size()
{
	return bottomright-topleft;
}

bool Rect::Contains_point(float x, float y)
{
	if(x<topleft.x || x>bottomright.x || y<topleft.y || y>bottomright.y)
	{
		return false;
	}
	return true;
}

}
