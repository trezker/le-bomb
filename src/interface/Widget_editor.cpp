#include "interface/Widget_editor.h"
#include "interface/Renderer.h"
#include "interface/Label.h"

namespace interface
{

Widget_editor::Widget_editor()
:widget(NULL)
,editing_attributes(false)
,pressed(false)
,left(false)
,right(false)
,top(false)
,bottom(false)
,move(false)
,selected(false)
{
	float margin = 4;
	attributes_max_y = 0;
	attribute_group = new Group;
	attribute_group->Set_bounding_rect(Rect(0, 0, 200, 400));

	Label* label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 200, 20));
	label->Set_text("Base attributes");
	attribute_group->Add_widget(label);
	attributes_max_y += 20;

	label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text("Top");
	attribute_group->Add_widget(label);
	attributes_max_y += 20;

	label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text("Left");
	attribute_group->Add_widget(label);
	attributes_max_y += 20;

	label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text("Width");
	attribute_group->Add_widget(label);
	attributes_max_y += 20;

	label = new Label;
	label->Set_bounding_rect(Rect(margin, attributes_max_y, 100, 20));
	label->Set_text("Height");
	attribute_group->Add_widget(label);
	attributes_max_y += 20;
}

Widget_editor::~Widget_editor()
{
	delete attribute_group;
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
		if(event.mouse.button == 1)
		{
			Rect brect = Get_bounding_rect();
			if(brect.Contains_point(event.mouse.x, event.mouse.y))
			{
				pressed = true;
				if(event.mouse.x < brect.Topleft().x+5)
				{
					pos.x = brect.Topleft().x;
					left = true;
				}
				else if(event.mouse.x > brect.Bottomright().x-5)
				{
					pos.x = brect.Bottomright().x;
					right = true;
				}
				if(event.mouse.y < brect.Topleft().y+5)
				{
					pos.y = brect.Topleft().y;
					top = true;
				}
				else if(event.mouse.y > brect.Bottomright().y-5)
				{
					pos.y = brect.Bottomright().y;
					bottom = true;
				}
				if(!(left || right || top || bottom))
				{
					move = true;
					pos = brect.Topleft();
				}
				if(!selected)
				{
					selected = true;
					Set_dirty(true);
				}
			}
			else if(selected)
			{
				selected = false;
				Set_dirty(true);
			}
		}
	}
	if(ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		if(event.mouse.button == 1)
		{
			pressed = false;
			left = false;
			right = false;
			top = false;
			bottom = false;
			move = false;

			Rect brect = Get_bounding_rect();
			if(selected && !brect.Contains_point(event.mouse.x, event.mouse.y))
			{
				selected = false;
				Set_dirty(true);
			}
		}
		if(event.mouse.button == 2)
		{
			Rect brect = Get_bounding_rect();
			if(brect.Contains_point(event.mouse.x, event.mouse.y))
			{
				editing_attributes = true;
				attribute_group->Move_to(event.mouse.x, event.mouse.y);
			}
		}
	}
	if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
		if(pressed)
		{
			pos += Vector2(event.mouse.dx, event.mouse.dy);
			Vector2 curpos(pos);
			ALLEGRO_KEYBOARD_STATE keyboard_state;
			al_get_keyboard_state(&keyboard_state);
			if(al_key_down(&keyboard_state, ALLEGRO_KEY_LCTRL))
			{
				curpos.x = int(pos.x/10)*10;
				curpos.y = int(pos.y/10)*10;
			}
			if(move)
			{
				Rect n = widget->Get_bounding_rect();
				n.Move_to(curpos.x, curpos.y);
				widget->Set_bounding_rect(n);
				Set_bounding_rect(n);
			}

			Vector2 topleft = Get_bounding_rect().Topleft();
			Vector2 bottomright = Get_bounding_rect().Bottomright();
			if(left && curpos.x < bottomright.x-15)
				topleft.x = curpos.x;
			if(right && curpos.x > topleft.x+15)
				bottomright.x = curpos.x;
			if(top && curpos.y < bottomright.y-15)
				topleft.y = curpos.y;
			if(bottom && curpos.y > topleft.y+15)
				bottomright.y = curpos.y;
			
			Rect n(topleft, bottomright);
			widget->Set_bounding_rect(n);
			Set_bounding_rect(n);
			Set_dirty(true);
		}
	}
	if (ALLEGRO_EVENT_KEY_DOWN == event.type)
	{
		if (ALLEGRO_KEY_ESCAPE == event.keyboard.keycode)
		{
			editing_attributes = false;
		}
	}

}

void Widget_editor::Render()
{
	widget->Render();
	if(selected)
	{
		int c = rand()%255;
		Renderer* renderer = Get_renderer();
		renderer->Draw_rect(Get_bounding_rect(), al_map_rgb(c, c, c));
	}
	if(editing_attributes)
	{
		Renderer* renderer = Get_renderer();
		renderer->Draw_raised_panel(attribute_group->Get_bounding_rect());
		attribute_group->Render();
	}
}

void Widget_editor::Set_widget(Widget* w)
{
	widget = w;
	Set_bounding_rect(widget->Get_bounding_rect());
}

}
