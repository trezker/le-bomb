#include "interface/Widget.h"

namespace interface
{

Widget::Widget()
:dirty(false)
,covers_mouse_down(true)
{
}

Widget::~Widget()
{
}

void Widget::Event(const ALLEGRO_EVENT &event)
{
}

void Widget::Render()
{
}

void Widget::Move_to(float x, float y)
{
	brect.Move_to(x, y);
}

void Widget::Move(float x, float y)
{
	brect.Move(x, y);
}

void Widget::Set_bounding_rect(const Rect& rect)
{
	brect = rect;
}

Rect Widget::Get_bounding_rect()
{
	return brect;
}

bool Widget::Is_dirty()
{
	return dirty;
}

void Widget::Set_dirty(bool t)
{
	dirty = t;
}

void Widget::Set_cover_mouse_down(bool active)
{
	covers_mouse_down = active;
}

bool Widget::Covers_mouse_down()
{
	return covers_mouse_down;
}

}
