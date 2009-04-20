#include "interface/Spinbox.h"
#include "interface/Renderer.h"
#include <sstream>

namespace interface
{

Spinbox::Spinbox()
:value(0)
{
	inputbox.Set_text("0");
	inputbox.Set_alignment(HALIGN_RIGHT);
}

Widget* Spinbox::Clone()
{
	return new Spinbox(*this);
}

void Spinbox::Event(const ALLEGRO_EVENT &event)
{
	if(Get_bounding_rect().Contains_point(event.mouse.x, event.mouse.y))
	{
		if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
		{
			value += event.mouse.dz;
			std::stringstream os;
			os<<value;
			std::string text;
			os>>text;
			inputbox.Set_text(text);
			return;
		}
	}
	
	inputbox.Event(event);
	std::string text = inputbox.Get_text();
	std::stringstream is(text);
	double d = 0;
	is >> d;
	if (!is.fail( ))
	{
		value = d;
	}
/*	else
	{
*/
		std::stringstream os;
		os<<value;
		os>>text;
		inputbox.Set_text(text);
//	}
}

void Spinbox::Render()
{
	Renderer* renderer = Get_renderer();
	Rect brect = Get_bounding_rect();
	float height = brect.Size().y;
	Vector2 tl = brect.Topleft();
	Vector2 br = brect.Bottomright();
	
	Rect up(br.x-height, tl.y, height, height/2);
	Rect down(br.x-height, tl.y+height/2, height, height/2);
	renderer->Draw_raised_panel(up);
	renderer->Draw_triangle(up, TRIANGLE_UP);
	renderer->Draw_raised_panel(down);
	renderer->Draw_triangle(down, TRIANGLE_DOWN);
	
	inputbox.Render();
}

void Spinbox::Set_value(float v)
{
	value = v;
}

float Spinbox::Get_value()
{
	return value;
}

void Spinbox::New_bounding_rect()
{
	Rect brect = Get_bounding_rect();
	float height = brect.Size().y;
	Vector2 tl = brect.Topleft();
	Vector2 br = brect.Bottomright();
	inputbox.Set_bounding_rect(Rect(tl.x, tl.y, brect.Size().x-height, height));
}

}
