#include "interface/Widget.h"

namespace interface
{

Widget::~Widget()
{
}

void Widget::Event(const ALLEGRO_EVENT &event)
{
}

void Widget::Render()
{
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

}
