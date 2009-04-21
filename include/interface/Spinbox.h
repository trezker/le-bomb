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
	virtual void New_bounding_rect();

	float value;
	Inputbox inputbox;
	Rect b_up;
	Rect b_down;
	bool press_up;
	bool press_down;
	float stepsize;
	float tick_cd;
	float ticktime;
};

}

#endif
