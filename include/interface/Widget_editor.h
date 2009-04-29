#ifndef interface_Widget_editor_h
#define interface_Widget_editor_h

#include "interface/Widget.h"
#include "interface/Group.h"
#include "interface/Spinbox.h"
#include "interface/Attribute_group.h"

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
	void Add_attribute_group(Attribute_group* a);
//	void Add_editable_attribute(std::string& label, Widget* control, float control_width);
protected:
	Widget* widget;
	Group* attribute_group;
	bool editing_attributes;
	float attributes_max_y;
private:
	bool pressed;
	bool left;
	bool right;
	bool top;
	bool bottom;
	bool move;
	bool selected;
	Vector2 pos;
	float attributes_height;
	Spinbox w_top;
	Spinbox w_left;
	Spinbox w_width;
	Spinbox w_height;

	typedef std::list<Attribute_group*> Attribute_groups;
	Attribute_groups attribute_groups;
};

}

#endif
