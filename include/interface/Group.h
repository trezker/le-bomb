#ifndef interface_Group_h
#define interface_Group_h

#include "interface/Widget.h"
#include <list>

namespace interface
{

class Group: public Widget
{
public:
	Group();
	virtual ~Group();
	virtual Widget* Clone();
	virtual void Event(const ALLEGRO_EVENT &event);
	virtual void Render();
	/* Allows you to have regular tab for groups that manages "low level" widgets
	 * and for instance CTRL+TAB for a group that manages groups.
	 * */
	void Set_tab_modifier(int m);
	void Add_widget(Widget* i);
	void Remove_widget(Widget* i);
	/* Puts the widget in the list of widgets you can tab to.
	 * */
	void Set_tab_order(Widget* i, int o=-1);
private:
	int tab_modifier;
	int tab_position;
	typedef std::list<Widget*> Widgets;
	Widgets widgets;
	Widgets tab_order;
	Widget* focus;
};

}

#endif
