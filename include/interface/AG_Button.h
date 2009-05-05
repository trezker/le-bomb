#ifndef interface_AG_Button_h
#define interface_AG_Button_h

#include "interface/Attribute_group.h"
#include "interface/Button.h"
#include "interface/Inputbox.h"

namespace interface
{

class AG_Button: public Attribute_group
{
public:
	AG_Button();
	virtual Widget* Clone();
	virtual void Set_widget(Widget* w);
	virtual void Event(ALLEGRO_EVENT event);
private:
	Inputbox text;
	Button* widget;
};

}

#endif
