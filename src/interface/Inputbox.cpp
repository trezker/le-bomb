#include "interface/Inputbox.h"
#include "interface/Renderer.h"
#include "interface/Events.h"

namespace interface
{

Inputbox::Inputbox()
:halignment(HALIGN_LEFT)
,pressed(false)
,input_focus(false)
,pos(0)
{
}

Widget* Inputbox::Clone()
{
	return new Inputbox(*this);
}

void Inputbox::Event(const ALLEGRO_EVENT &event)
{
	if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN == event.type)
	{
		if(Get_bounding_rect().Contains_point(event.mouse.x, event.mouse.y))
		{
			pressed = true;
		}
	}
	if(ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		if(Get_bounding_rect().Contains_point(event.mouse.x, event.mouse.y))
		{
			if(pressed)
			{
				input_focus = true;
				Set_dirty(true);
			}
		}
		else if(input_focus == true)
		{
			input_focus = false;
			Set_dirty(true);
		}
		if(pressed)
		{
			pressed = false;
		}
	}
	if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
	}
	if(input_focus && (ALLEGRO_EVENT_KEY_DOWN == event.type || ALLEGRO_EVENT_KEY_REPEAT == event.type))
	{
//		int pos = text.length();
		bool special_key = false;
		switch(event.keyboard.keycode)
		{
		case ALLEGRO_KEY_LEFT:
			--pos;
			special_key = true;
			break;

		case ALLEGRO_KEY_RIGHT:
			++pos;
			special_key = true;
			break;

		case ALLEGRO_KEY_BACKSPACE:
			if(pos>0)
			{
				--pos;
				text.erase(pos, 1);
			}
			special_key = true;
			break;

		case ALLEGRO_KEY_ENTER:
		case ALLEGRO_KEY_PAD_ENTER:
			interface::Event e;
			e.source = this;
			e.type = "Send";
			Emit_event(e);
			special_key = true;
			break;
		}
		if(!special_key)
		{
			char s[5];
			int n = al_utf8_encode(s, event.keyboard.unichar);
			text.insert(pos, s, n);
			++pos;
		}
		if(pos<0)
			pos = 0;
		if(pos>int(text.length()))
			pos = text.length();
		Set_dirty(true);
	}
}

void Inputbox::Render()
{
	Renderer* renderer = Get_renderer();
	renderer->Draw_text_field(Get_bounding_rect());
	Rect text_rect = Get_bounding_rect();
	text_rect.Shrink(2, 2);
	renderer->Draw_text(text_rect, text, halignment, VALIGN_TOP, al_map_rgb(0, 0, 0));
	
	Vector2 tl = text_rect.Topleft();
	Vector2 br = text_rect.Bottomright();

	int posx = al_get_text_width(renderer->Get_font(), text.substr(0, pos).c_str());
	Rect cur(tl.x+posx, tl.y, 1, br.y-tl.y);
	renderer->Draw_rect(cur, al_map_rgb(222, 222, 222));
}

void Inputbox::Set_text(const std::string& t)
{
	text = t;
}

void Inputbox::Set_alignment(HAlignment a)
{
	halignment = a;
}

std::string Inputbox::Get_text()
{
	return text;
}

}
