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
	virtual Widget* Clone();
	virtual void Event(const ALLEGRO_EVENT &event);
	virtual void Render();
	void Set_toggle(bool t);
	bool Get_toggle();
	void Set_radio(bool t);
	bool Get_radio();
	void Press();
	void Release();
	void Set_text(const std::string& text);
	std::string Get_text();
private:
	//Was pressed by mouse, mouse not released yet
	bool pressed;
	//Mouse is over it
	bool mouse_over;
	//Button locked in down position.
	bool activated;
	//Button toggles
	bool toggle;
	bool radio;
	Label* label;
};

}

#endif
