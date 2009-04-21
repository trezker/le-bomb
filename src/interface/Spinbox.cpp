#include "interface/Spinbox.h"
#include "interface/Renderer.h"
#include <sstream>

namespace interface
{

Spinbox::Spinbox()
:value(0)
,press_up(false)
,press_down(false)
,stepsize(1)
,tick_cd(0)
,ticktime(.25)
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
	if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN == event.type)
	{
		if(b_up.Contains_point(event.mouse.x, event.mouse.y))
		{
			press_up = true;
			Set_dirty(true);
		}
		if(b_down.Contains_point(event.mouse.x, event.mouse.y))
		{
			press_down = true;
			Set_dirty(true);
		}
	}
	if(ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		if(press_up)
		{
			press_up = false;
			Set_dirty(true);
		}
		if(press_down)
		{
			press_down = false;
			Set_dirty(true);
		}
		tick_cd = 0;
		ticktime = .25;
	}

	if(EVENT_UPDATE == event.type)
	{
		UPDATE_EVENT* ue = (UPDATE_EVENT*)event.user.data1;
		//Todo: ticks, stepsize
		if(press_up || press_down)
		{
			tick_cd-=ue->dt;
			if(tick_cd<=0)
			{
				ticktime*=.95;
				tick_cd+=ticktime;
			
				if(press_up)
					value += stepsize;
				if(press_down)
					value -= stepsize;
				Set_value(value);
			}
		}
		return;
	}
	
	if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
		if(Get_bounding_rect().Contains_point(event.mouse.x, event.mouse.y))
		{
			value += event.mouse.dz;
			Set_value(value);
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
		Set_value(value);
//	}
}

void Spinbox::Render()
{
	Renderer* renderer = Get_renderer();
	Rect brect = Get_bounding_rect();
	float height = brect.Size().y;
	Vector2 tl = brect.Topleft();
	Vector2 br = brect.Bottomright();

	if(!press_up)
		renderer->Draw_raised_panel(b_up);
	else
		renderer->Draw_sunken_panel(b_up);
	renderer->Draw_triangle(b_up, TRIANGLE_UP);
	if(!press_down)
		renderer->Draw_raised_panel(b_down);
	else
		renderer->Draw_sunken_panel(b_down);
	renderer->Draw_triangle(b_down, TRIANGLE_DOWN);
	
	inputbox.Render();
}

void Spinbox::Set_value(float v)
{
	value = v;

	std::stringstream os;
	os<<value;
	std::string text;
	os>>text;
	inputbox.Set_text(text);
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
	b_up.Set(br.x-height, tl.y, height, height/2);
	b_down.Set(br.x-height, tl.y+height/2, height, height/2);
}

}
