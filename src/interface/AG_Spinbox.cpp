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
	float margin = 4;
	float attributes_max_y = 0;

	Label* label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 200, 20));
	label->Set_text("Spinbox attributes");
	Add_widget(label);
	attributes_max_y += 20;

	//Attribute Value
	label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text("Value");
	Add_widget(label);

	value.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 100, 20));
	Add_widget(&value);
	attributes_max_y += 20;
}

void AG_Spinbox::Event(ALLEGRO_EVENT event)
{
	Group::Event(event);
	float v = value.Get_value();
	widget->Set_value(v);
//	printf("%f, %f", v, widget->Get_value());
}

}
