#include "interface/AG_Spinbox.h"
#include "interface/Label.h"

namespace interface
{

Widget* AG_Spinbox::Clone()
{
	return new AG_Spinbox();
}

void AG_Spinbox::Set_widget(Widget* w)
{
	widget = dynamic_cast<Spinbox*>(w);
}

AG_Spinbox::AG_Spinbox()
{
	Label* label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 200, 20));
	label->Set_text("Spinbox attributes");
	Add_widget(label);

	//Attribute Value
	New_attribute("Value");
	value.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 100, 20));
	Add_widget(&value);
}

void AG_Spinbox::Event(ALLEGRO_EVENT event)
{
	Group::Event(event);
	float v = value.Get_value();
	widget->Set_value(v);
}

}
