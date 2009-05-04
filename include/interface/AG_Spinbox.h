#ifndef interface_AG_Spinbox_h
#define interface_AG_Spinbox_h

#include "interface/Attribute_group.h"
#include "interface/Spinbox.h"

namespace interface
{

class Spinbox_attribute_group: public Attribute_group
{
public:
	Spinbox_attribute_group();
	virtual void Set_widget(Widget* w);
	virtual void Event(ALLEGRO_EVENT event);
private:
	Spinbox value;
	Spinbox* widget;
};

}

#endif
