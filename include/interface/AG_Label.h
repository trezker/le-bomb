#ifndef interface_AG_Label_h
#define interface_AG_Label_h

#include "interface/Attribute_group.h"
#include "interface/Label.h"
#include "interface/Inputbox.h"
#include "interface/Button.h"

namespace interface
{

class AG_Label: public Attribute_group
{
public:
	AG_Label();
	virtual Widget* Clone();
	virtual void Set_widget(Widget* w);
	virtual void Event(ALLEGRO_EVENT event);
private:
	Inputbox text;
	Button align_left, align_center, align_right;
	Button valign_top, valign_center, valign_bottom;
	Label* widget;
};

}

#endif
