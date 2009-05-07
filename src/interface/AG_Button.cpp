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
	text.Set_text(widget->Get_text());
}

AG_Button::AG_Button()
{
	Label* label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 200, 20));
	label->Set_text("Button attributes");
	Add_widget(label);

	//Attribute Text
	New_attribute("Text");
	text.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 100, 20));
	Add_widget(&text);
}

void AG_Button::Event(ALLEGRO_EVENT event)
{
	Group::Event(event);
	std::string t = text.Get_text();
	widget->Set_text(t);
}

}
