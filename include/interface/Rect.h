#ifndef interface_Rect_h
#define interface_Rect_h

#include "math/Vector2.h"

namespace interface
{

class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h);
	Rect(Vector2 tl, Vector2 br);
	void Set(float x, float y, float w, float h);
	void Move(float dx, float dy);
	Vector2 Topleft();
	Vector2 Bottomright();
	Vector2 Size();

	bool Contains_point(float x, float y);
private:
	Vector2 topleft;
	Vector2 bottomright;
};

}

#endif
