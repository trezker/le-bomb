#include "interface/Widget_editor.h"
#include "interface/Renderer.h"

namespace interface
{

Widget_editor::Widget_editor()
:widget(NULL)
,pressed(false)
,left(false)
,right(false)
,top(false)
,bottom(false)
,move(false)
{
}

Widget_editor::~Widget_editor()
{
}

Widget* Widget_editor::Clone()
{
	Widget_editor* we = new Widget_editor(*this);
	we->widget = widget->Clone();
	return we;
}

void Widget_editor::Event(const ALLEGRO_EVENT &event)
{
	if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN == event.type)
	{
		Rect brect = Get_bounding_rect();
		if(brect.Contains_point(event.mouse.x, event.mouse.y))
		{
			pressed = true;
			if(event.mouse.x < brect.Topleft().x+5)
				left = true;
			else if(event.mouse.x > brect.Bottomright().x-5)
				right = true;
			if(event.mouse.y < brect.Topleft().y+5)
				top = true;
			else if(event.mouse.y > brect.Bottomright().y-5)
				bottom = true;
			if(!(left || right || top || bottom))
				move = true;
		}
	}
	if(ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		pressed = false;
		left = false;
		right = false;
		top = false;
		bottom = false;
		move = false;
	}
	if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
		if(pressed)
		{
			if(move)
			{
				Rect n = widget->Get_bounding_rect();
				n.Move(event.mouse.dx, event.mouse.dy);
				widget->Set_bounding_rect(n);
				Set_bounding_rect(n);
			}

			Vector2 topleft = Get_bounding_rect().Topleft();
			Vector2 bottomright = Get_bounding_rect().Bottomright();
			if(left && event.mouse.x < bottomright.x-15)
				topleft.x = event.mouse.x;
			if(right && event.mouse.x > topleft.x+15)
				bottomright.x = event.mouse.x;
			if(top && event.mouse.y < bottomright.y-15)
				topleft.y = event.mouse.y;
			if(bottom && event.mouse.y > topleft.y+15)
				bottomright.y = event.mouse.y;
			
			Rect n(topleft, bottomright);
			widget->Set_bounding_rect(n);
			Set_bounding_rect(n);
			Set_dirty(true);
		}
/*		if(Get_bounding_rect().Contains_point(event.mouse.x, event.mouse.y))
		{
			mouse_over = true;
		}
		else
		{
			mouse_over = false;
		}
*/
	}
}

void Widget_editor::Render()
{
	widget->Render();
	int c = rand()%255;
	Renderer* renderer = Get_renderer();
	renderer->Draw_rect(Get_bounding_rect(), al_map_rgb(c, c, c));
}

void Widget_editor::Set_widget(Widget* w)
{
	widget = w;
	Set_bounding_rect(widget->Get_bounding_rect());
}


}
