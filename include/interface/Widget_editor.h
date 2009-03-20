#ifndef interface_Widget_editor_h
#define interface_Widget_editor_h

#include "interface/Widget.h"

namespace interface
{

class Widget_editor: public Widget
{
public:
	Widget_editor();
	~Widget_editor();
	virtual Widget* Clone();
	virtual void Event(const ALLEGRO_EVENT &event);
	virtual void Render();
	void Set_widget(Widget* w);
private:
	Widget* widget;
	bool pressed;
	bool left;
	bool right;
	bool top;
	bool bottom;
	bool move;
};

}

#endif
