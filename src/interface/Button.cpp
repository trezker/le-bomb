#include "interface/Button.h"
#include "interface/Renderer.h"
#include "interface/Events.h"

namespace interface
{

Button::Button()
:pressed(false)
,mouse_over(false)
,activated(false)
,toggle(false)
,label(NULL)
{
}

Button::~Button()
{
}

Widget* Button::Clone()
{
	Button* b = new Button(*this);
	if(label)
		b->label = dynamic_cast<Label*>(label->Clone());
	return b;
}

void Button::Event(const ALLEGRO_EVENT &event)
{
	if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN == event.type)
	{
		if(Get_bounding_rect().Contains_point(event.mouse.x, event.mouse.y))
		{
			pressed = true;
			mouse_over = true;
			Set_dirty(true);
		}
	}
	if(ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		if(pressed && Get_bounding_rect().Contains_point(event.mouse.x, event.mouse.y))
		{
			if(toggle)
			{
				activated = !activated;
			}
			else
			{
				interface::Event e;
				e.source = this;
				e.type = "Activated";
				Emit_event(e);
			}
		}
		if(pressed)
		{
			pressed = false;
			Set_dirty(true);
		}
	}
	if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
		if(Get_bounding_rect().Contains_point(event.mouse.x, event.mouse.y))
		{
			mouse_over = true;
		}
		else
		{
			mouse_over = false;
		}
	}
}

void Button::Render()
{
	Renderer* renderer = Get_renderer();
	if((pressed && mouse_over) || (activated && toggle))
	{
		renderer->Draw_sunken_panel(Get_bounding_rect());
	}
	else
	{
		renderer->Draw_raised_panel(Get_bounding_rect());
	}
	if(label)
	{
		label->Set_bounding_rect(Get_bounding_rect());
		label->Render();
	}
}

void Button::Set_label(const std::string& text)
{
	if(label == NULL)
	{
		label = new Label;
		label->Set_bounding_rect(Get_bounding_rect());
	}
	label->Set_text(text);
	label->Set_alignment(HALIGN_CENTER);
	label->Set_vertical_alignment(VALIGN_CENTER);
}

}
