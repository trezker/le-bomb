#ifndef Widget_h
#define Widget_h

#include <allegro5/allegro5.h>
#include "interface/Rect.h"

namespace interface
{

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
	virtual ~Widget();
	virtual void Event(const ALLEGRO_EVENT &event);
	virtual void Render();
	void Set_bounding_rect(const Rect& rect);
	Rect Get_bounding_rect();
	bool Is_dirty();
	void Set_dirty(bool t);
private:
	Rect brect;
	bool dirty;
};

}

#endif
