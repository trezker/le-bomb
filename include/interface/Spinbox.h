#ifndef interface_Spinbox_h
#define interface_Spinbox_h

#include "interface/Widget.h"
#include "interface/Inputbox.h"
#include <string>

namespace interface
{

class Spinbox: public Widget
{
public:
	Spinbox();
	virtual Widget* Clone();
	virtual void Event(const ALLEGRO_EVENT &event);
	virtual void Render();
	void Set_value(float v);
	float Get_value();
private:
	float value;
	Inputbox inputbox;
	virtual void New_bounding_rect();
};

}

#endif
