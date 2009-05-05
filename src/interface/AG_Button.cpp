#include "interface/AG_Button.h"
#include "interface/Label.h"

namespace interface
{

Widget* AG_Button::Clone()
{
	return new AG_Button();
}

void AG_Button::Set_widget(Widget* w)
{
	widget = dynamic_cast<Button*>(w);
}

AG_Button::AG_Button()
{
	float margin = 4;
	float attributes_max_y = 0;

	Label* label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 200, 20));
	label->Set_text("Button attributes");
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

void AG_Button::Event(ALLEGRO_EVENT event)
{
	Group::Event(event);
	std::string t = text.Get_text();
	widget->Set_label(t);
}

}
