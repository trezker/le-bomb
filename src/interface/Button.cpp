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
,radio(false)
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
			if(toggle || radio)
			{
				activated = !activated;
				if(activated)
				{
					interface::Event e;
					e.source = this;
					e.type = "Activated";
					Emit_event(e);
				}
				else
				{
					if(radio)
					{
						activated = true;
					}
					else
					{
						interface::Event e;
						e.source = this;
						e.type = "Deactivated";
						Emit_event(e);
					}
				}
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
	if((pressed && mouse_over) || (activated))
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

void Button::Set_toggle(bool t)
{
	toggle = t;
}

bool Button::Get_toggle()
{
	return toggle;
}

void Button::Set_radio(bool t)
{
	radio = t;
}

bool Button::Get_radio()
{
	return radio;
}

void Button::Press()
{
	if(!activated)
	{
		activated = true;
		interface::Event e;
		e.source = this;
		e.type = "Activated";
		Emit_event(e);
	}
}

void Button::Release()
{
	if(activated)
	{
		activated = false;
		interface::Event e;
		e.source = this;
		e.type = "Deactivated";
		Emit_event(e);
	}
}

void Button::Set_text(const std::string& text)
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

std::string Button::Get_text()
{
	return label->Get_text();
}

}
