#include "interface/AG_Label.h"

namespace interface
{

Widget* AG_Label::Clone()
{
	return new AG_Label();
}

void AG_Label::Set_widget(Widget* w)
{
	widget = dynamic_cast<Label*>(w);
	text.Set_text(widget->Get_text());
}

AG_Label::AG_Label()
{
	float margin = 4;
	float attributes_max_y = 0;

	Label* label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 200, 20));
	label->Set_text("Label attributes");
	Add_widget(label);
	attributes_max_y += 20;

	//Attribute Value
	label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text("Text");
	Add_widget(label);

	text.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 100, 20));
	Add_widget(&text);
	attributes_max_y += 20;
}

void AG_Label::Event(ALLEGRO_EVENT event)
{
	Group::Event(event);
	std::string t = text.Get_text();
	widget->Set_text(t);
}

}
