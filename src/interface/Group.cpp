#include "interface/Group.h"
#include <algorithm>

namespace interface
{

Group::Group()
:tab_modifier(0)
,tab_position(-1)
,focus(NULL)
{
}

Group::~Group()
{
}

Widget* Group::Clone()
{
	return new Group(*this);
}

void Group::Event(const ALLEGRO_EVENT &event)
{
	for(Widgets::iterator i =  widgets.begin(); i != widgets.end(); ++i)
	{
		(*i)->Event(event);
	}
}

void Group::Render()
{
	for(Widgets::iterator i =  widgets.begin(); i != widgets.end(); ++i)
	{
		(*i)->Render();
	}
}

void Group::Set_tab_modifier(int m)
{
	tab_modifier = m;
}

void Group::Add_widget(Widget* i)
{
	widgets.push_back(i);
}

void Group::Remove_widget(Widget* i)
{
	Widgets::iterator it = std::find(widgets.begin(), widgets.end(), i);
	if(it!=widgets.end())
		widgets.erase(it);
	it = std::find(tab_order.begin(), tab_order.end(), i);
	if(it!=tab_order.end())
		tab_order.erase(it);
}

void Group::Set_tab_order(Widget* i, int o)
{
	if(o==-1 || o>=static_cast<int>(tab_order.size()))
		tab_order.push_back(i);
	else
		tab_order.insert(tab_order.begin()+o, i);
}

}
