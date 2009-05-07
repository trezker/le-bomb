#include "interface/AG_Button.h"
#include "interface/Label.h"
#include "interface/Events.h"

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

	New_attribute("Text");
	text.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 100, 20));
	Add_widget(&text);

	New_attribute("Toggle");
	toggle.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 100, 20));
	toggle.Set_toggle(true);
	Add_widget(&toggle);

	New_attribute("Radio");
	radio.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 100, 20));
	radio.Set_toggle(true);
	Add_widget(&radio);
}

void AG_Button::Event(ALLEGRO_EVENT event)
{
	Push_event_queues();
	Event_queue event_queue;
	Add_event_queue(&event_queue);

	Group::Event(event);
	std::string t = text.Get_text();
	widget->Set_text(t);
	
	while(!event_queue.Empty())
	{
		interface::Event e = event_queue.Get_next_event();

		if(e.type == "Activated")
		{
			if(e.source == &toggle)
			{
				widget->Set_toggle(true);
			}
			if(e.source == &radio)
			{
				widget->Set_radio(true);
			}
		}
		if(e.type == "Deactivated")
		{
			if(e.source == &toggle)
			{
				widget->Set_toggle(false);
			}
			if(e.source == &radio)
			{
				widget->Set_radio(false);
			}
		}
	}
}

}
