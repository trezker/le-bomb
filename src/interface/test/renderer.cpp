#include <allegro5/allegro5.h>
#include <allegro5/a5_opengl.h>
#include <allegro5/a5_iio.h>
#include <allegro5/a5_font.h>
#include <allegro5/a5_ttf.h>
#include <iostream>
#include "interface/Renderer.h"
#include "interface/Button.h"
#include "interface/Rect.h"
#include "interface/Events.h"
#include "interface/Label.h"
#include "interface/Widget_editor.h"
#include "interface/Group.h"

interface::Renderer* renderer = NULL;
interface::Group* root_interface;
interface::Group* edit_interface;

typedef std::vector<interface::Widget*> Widgets;
Widgets root_widgets;
Widgets edit_widgets;
Widgets prototypes;

//interface::Button* button;
interface::Label* label_left;
interface::Label* label_right;
interface::Label* label_center;
interface::Widget_editor* widget_editor;
interface::Event_queue event_queue;
ALLEGRO_FONT* font = NULL;

bool Init()
{
	interface::Add_event_queue(&event_queue);

	renderer = new interface::Renderer();
	interface::Set_renderer(renderer);
	font = al_ttf_load_font("media/DejaVuSans.ttf", -12, 0);
	renderer->Set_font(font);
/*
	button = new interface::Button();
	button->Set_bounding_rect(interface::Rect(120, 120, 100, 20));
	button->Set_label("Ze button");
	renderer->Add_widget(button);
	
	label_left = new interface::Label();
	label_left->Set_bounding_rect(interface::Rect(120, 150, 100, 30));
	label_left->Set_text("top left");
//	renderer->Add_widget(label_left);
	
	widget_editor = new interface::Widget_editor;
	widget_editor->Set_widget(label_left);
	renderer->Add_widget(widget_editor);

	label_right = new interface::Label();
	label_right->Set_bounding_rect(interface::Rect(120, 200, 100, 30));
	label_right->Set_text("bottom right");
	label_right->Set_alignment(interface::HALIGN_RIGHT);
	label_right->Set_vertical_alignment(interface::VALIGN_BOTTOM);
	renderer->Add_widget(label_right);

	label_center = new interface::Label();
	label_center->Set_bounding_rect(interface::Rect(120, 250, 100, 30));
	label_center->Set_text("center_center");
	label_center->Set_alignment(interface::HALIGN_CENTER);
	label_center->Set_vertical_alignment(interface::VALIGN_CENTER);
	renderer->Add_widget(label_center);
*/

	interface::Button* button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 0, 100, 20));
	button->Set_label("Button");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Button* button_prototype = new interface::Button;
	button_prototype->Set_bounding_rect(interface::Rect(0, 0, 100, 20));
	button_prototype->Set_label("Button");
	prototypes.push_back(button_prototype);

	button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 20, 100, 20));
	button->Set_label("Label");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Label* label_prototype = new interface::Label;
	label_prototype->Set_bounding_rect(interface::Rect(0, 0, 100, 20));
	label_prototype->Set_text("Label");
	prototypes.push_back(label_prototype);

	root_interface = new interface::Group;
	edit_interface = new interface::Group;
	root_interface->Add_widget(edit_interface);

	for(Widgets::iterator i = root_widgets.begin(); i != root_widgets.end(); ++i)
		root_interface->Add_widget(*i);
	
	return true;
}

void Shutdown()
{
//	delete button;
	delete renderer;
	renderer = NULL;
	interface::Set_renderer(NULL);
}

void Update(double dt)
{
}

void Render()
{
/*	interface::Rect rect(10, 10, 100, 100);
	renderer->Draw_raised_panel(rect);

	rect.Set(120, 10, 100, 100);
	renderer->Draw_sunken_panel(rect);
*/	
	renderer->Render();
}

void Event(ALLEGRO_EVENT event)
{
	root_interface->Event(event);
	
	interface::Event e = event_queue.Get_next_event();
/*	if(e.source == button && e.type == "Activated")
	{
		printf("Button activated\n");
	}
*/	if(e.type == "Activated")
	{
		for(unsigned int i = 0; i < root_widgets.size(); ++i)
		{
				printf("Woot\n");
			if(root_widgets[i] == e.source)
			{
				interface::Widget* n = prototypes[i]->Clone();
				edit_widgets.push_back(n);

				interface::Widget_editor* widget_editor = new interface::Widget_editor;
				widget_editor->Set_widget(n);
				renderer->Add_widget(widget_editor);
				edit_interface->Add_widget(widget_editor);
				break;
			}
		}
	}
}

int main()
{
	al_init();
	al_install_mouse();
	al_install_keyboard();
	al_iio_init();
	al_font_init();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 24, ALLEGRO_REQUIRE);
	int width = 800;
	int height = 600;
 	display = al_create_display(width, height);
 	if(!display)
 	{
 		printf("Failed to create display\n");
 		return 0;
	}

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)al_get_keyboard());
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)al_get_mouse());

	if(!Init())
		return 0;

	double last_time = al_current_time();

	bool quit = false;

	while(!quit)
	{
		ALLEGRO_EVENT event;
		while (al_get_next_event(event_queue, &event))
		{
		  	if (ALLEGRO_EVENT_KEY_DOWN == event.type)
			{
				if (ALLEGRO_KEY_ESCAPE == event.keyboard.keycode)
				{
					quit = true;
				}
			}
			if (ALLEGRO_EVENT_DISPLAY_CLOSE == event.type)
			{
				quit = true;
			}
			Event(event);
		}
		if (quit)
			break;

		double current_time = al_current_time();
		double dt = current_time - last_time;
		last_time = current_time;
		Update(dt);

		al_clear(al_map_rgb(0, 0, 0));
		Render();
		al_flip_display();

		al_rest(0.001);
	}

	Shutdown();

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}
