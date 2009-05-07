#ifndef Attribute_group_h
#define Attribute_group_h

#include "interface/Group.h"
#include <string>

namespace interface
{

//Only use one instance of each type of group.
//Todo: implement, collapsable.
class Attribute_group: public Group
{
public:
	Attribute_group();
	virtual void Set_widget(Widget* w) =0;
	//The group total height 
	float Get_height();
	void Set_height(float h);
	void New_attribute(const std::string& text);
	virtual void Event(ALLEGRO_EVENT event);
protected:
	float height;
	float margin;
	float attributes_max_y;
};

}

#endif
