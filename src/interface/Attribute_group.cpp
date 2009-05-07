#include "interface/Attribute_group.h"
#include "interface/Label.h"

namespace interface
{

Attribute_group::Attribute_group()
:height(0)
,margin(4)
,attributes_max_y(0)
{
}

float Attribute_group::Get_height()
{
	return height;
}

void Attribute_group::Set_height(float h)
{
	height = h;
}

void Attribute_group::New_attribute(const std::string& text)
{
	attributes_max_y += 20;
	Label* label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text(text);
	Add_widget(label);
}

void Attribute_group::Event(ALLEGRO_EVENT event)
{
}

}
