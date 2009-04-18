#ifndef interface_Inputbox_h
#define interface_Inputbox_h

#include "interface/Widget.h"
#include <string>

namespace interface
{

class Inputbox: public Widget
{
public:
	Inputbox();
	virtual Widget* Clone();
	virtual void Event(const ALLEGRO_EVENT &event);
	virtual void Render();
	void Set_text(const std::string& t);
	void Set_alignment(HAlignment a);
	std::string Get_text();
private:
	std::string text;
	HAlignment halignment;
	bool pressed;
	bool input_focus;
	int pos;
};

}

#endif
