#ifndef interface_Button_h
#define interface_Button_h

#include <interface/Widget.h>
#include <interface/Label.h>

namespace interface
{

class Button: public Widget
{
public:
	Button();
	virtual ~Button();
	virtual void Event(const ALLEGRO_EVENT &event);
	virtual void Render();
	void Set_label(const std::string& text);
private:
	//Was pressed by mouse, mouse not released yet
	bool pressed;
	//Mouse is over it
	bool mouse_over;
	//Button locked in down position.
	bool activated;
	//Button toggles
	bool toggle;
	Label* label;
};

}

#endif
