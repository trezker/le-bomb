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

Rect::Rect(Vector2 tl, Vector2 br)
{
	topleft = tl;
	bottomright = br;
}

void Rect::Set(float x, float y, float w, float h)
{
	topleft.Set(x, y);
	bottomright.Set(x+w, y+h);
}

void Rect::Move(float dx, float dy)
{
	Vector2 d(dx, dy);
	topleft += d;
	bottomright += d;
}

void Rect::Shrink(float dx, float dy)
{
	topleft.x += dx;
	topleft.y += dy;
	bottomright.x -= dx;
	bottomright.y -= dy;
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
