#include "interface/AG_Label.h"
#include "interface/Events.h"

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

	//Attribute Text
	label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text("Text");
	Add_widget(label);

	text.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 100, 20));
	Add_widget(&text);
	attributes_max_y += 20;

	//Attribute Alignment
	label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text("Alignment");
	Add_widget(label);

	align_left.Set_bounding_rect(interface::Rect(100-margin, attributes_max_y, 33, 20));
	align_left.Set_radio(true);
	align_left.Set_text("L");
	align_left.Press();
	align_center.Set_bounding_rect(interface::Rect(134-margin, attributes_max_y, 33, 20));
	align_center.Set_radio(true);
	align_center.Set_text("C");
	align_right.Set_bounding_rect(interface::Rect(168-margin, attributes_max_y, 33, 20));
	align_right.Set_radio(true);
	align_right.Set_text("R");

	Add_widget(&align_left);
	Add_widget(&align_center);
	Add_widget(&align_right);
	attributes_max_y += 20;
}

void AG_Label::Event(ALLEGRO_EVENT event)
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
			if(e.source == &align_left)
			{
				widget->Set_alignment(interface::HALIGN_LEFT);
				align_center.Release();
				align_right.Release();
			}
			if(e.source == &align_right)
			{
				widget->Set_alignment(interface::HALIGN_RIGHT);
				align_center.Release();
				align_left.Release();
			}
			if(e.source == &align_center)
			{
				widget->Set_alignment(interface::HALIGN_CENTER);
				align_right.Release();
				align_left.Release();
			}
		}
	}
	Pop_event_queues();
}

}
