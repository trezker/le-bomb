#ifndef Widget_h
#define Widget_h

#include <allegro5/allegro5.h>
#include "interface/Rect.h"

namespace interface
{

#define EVENT_UPDATE 1025

struct UPDATE_EVENT
{
	double dt;
};


enum HAlignment
{
	HALIGN_LEFT, HALIGN_RIGHT, HALIGN_CENTER
};
enum VAlignment
{
	VALIGN_TOP, VALIGN_BOTTOM, VALIGN_CENTER
};

class Widget
{
public:
	Widget();
	virtual ~Widget();
	virtual Widget* Clone()=0;
	virtual void Event(const ALLEGRO_EVENT &event);
	virtual void Render();
	virtual void Move_to(float x, float y);
	virtual void Move(float x, float y);
	void Set_bounding_rect(const Rect& rect);
	Rect Get_bounding_rect();
	bool Is_dirty();
	void Set_dirty(bool t);

	void Set_cover_mouse_down(bool active);
	bool Covers_mouse_down();
private:
	virtual void New_bounding_rect();

	Rect brect;
	bool dirty;
	bool covers_mouse_down;
};

}

#endif
