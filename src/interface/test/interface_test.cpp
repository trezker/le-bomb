#include <allegro5/allegro5.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "interface/Renderer.h"
#include "interface/Button.h"
#include "interface/Rect.h"
#include "interface/Events.h"
#include "interface/Label.h"
#include "interface/Inputbox.h"
#include "interface/Spinbox.h"
#include "interface/Widget_editor.h"
#include "interface/Group.h"
#include "interface/Attribute_group.h"
#include "interface/Attribute_groups.h"
#include <cstdio>

interface::Renderer* renderer = NULL;
interface::Group* root_interface;
interface::Group* edit_interface;

typedef std::vector<interface::Widget*> Widgets;
Widgets root_widgets;
Widgets edit_widgets;
Widgets editor_prototypes;
Widgets prototypes;
typedef std::map<interface::Widget*, interface::Attribute_group*> Attribute_groups;
Attribute_groups attribute_groups;



interface::Button* button_left;
interface::Button* button_right;
interface::Button* button_center;
interface::Inputbox* inputbox;
interface::Spinbox* spinbox;

interface::Label* label_left;
interface::Label* label_right;
interface::Label* label_center;
interface::Widget_editor* widget_editor;
interface::Event_queue event_queue;
ALLEGRO_FONT* font = NULL;

int width = 800;
int height = 600;

bool Init()
{
	interface::Add_event_queue(&event_queue);

	renderer = new interface::Renderer();
	interface::Set_renderer(renderer);
	font = al_load_ttf_font("media/DejaVuSans.ttf", -12, 0);
	renderer->Set_font(font);

	//Button
	interface::Button* button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 0, 100, 20));
	button->Set_text("Button");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Button* button_prototype = new interface::Button;
	button_prototype->Set_bounding_rect(interface::Rect(100, 0, 100, 20));
	button_prototype->Set_text("Button");
	prototypes.push_back(button_prototype);

	attribute_groups[button] = new interface::AG_Button;

	//Label
	button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 20, 100, 20));
	button->Set_text("Label");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Label* label_prototype = new interface::Label;
	label_prototype->Set_bounding_rect(interface::Rect(100, 0, 100, 20));
	label_prototype->Set_text("Label");
	prototypes.push_back(label_prototype);

	attribute_groups[button] = new interface::AG_Label;

	//Inputbox
	button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 40, 100, 20));
	button->Set_text("Inputbox");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Inputbox* inputbox_prototype = new interface::Inputbox;
	inputbox_prototype->Set_bounding_rect(interface::Rect(100, 0, 100, 20));
	inputbox_prototype->Set_text("Inputbox");
	prototypes.push_back(inputbox_prototype);

	//Spinbox
	button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 60, 100, 20));
	button->Set_text("Spinbox");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Spinbox* spinbox_prototype = new interface::Spinbox;
	spinbox_prototype->Set_bounding_rect(interface::Rect(100, 0, 100, 20));
	prototypes.push_back(spinbox_prototype);

	attribute_groups[button] = new interface::AG_Spinbox;


	root_interface = new interface::Group;
	root_interface->Set_bounding_rect(interface::Rect(0, 0, width, height));
	edit_interface = new interface::Group;
	edit_interface->Set_bounding_rect(interface::Rect(100, 0, width-100, height));
	root_interface->Add_widget(edit_interface);

	for(Widgets::iterator i = root_widgets.begin(); i != root_widgets.end(); ++i)
		root_interface->Add_widget(*i);

	inputbox = new interface::Inputbox;
	inputbox->Set_bounding_rect(interface::Rect(100, 100, 100, 20));
	inputbox->Set_text("Inputbox");
	renderer->Add_widget(inputbox);
	root_interface->Add_widget(inputbox);

	button_left = new interface::Button;
	button_left->Set_bounding_rect(interface::Rect(100, 120, 33, 20));
	button_left->Set_radio(true);
	button_left->Press();
	button_center = new interface::Button;
	button_center->Set_bounding_rect(interface::Rect(134, 120, 33, 20));
	button_center->Set_radio(true);
	button_right = new interface::Button;
	button_right->Set_bounding_rect(interface::Rect(168, 120, 33, 20));
	button_right->Set_radio(true);

	renderer->Add_widget(button_left);
	renderer->Add_widget(button_center);
	renderer->Add_widget(button_right);
	root_interface->Add_widget(button_left);
	root_interface->Add_widget(button_center);
	root_interface->Add_widget(button_right);

	spinbox = new interface::Spinbox;
	spinbox->Set_bounding_rect(interface::Rect(100, 80, 100, 20));
	renderer->Add_widget(spinbox);
	root_interface->Add_widget(spinbox);

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
	
	while(!event_queue.Empty())
	{
		interface::Event e = event_queue.Get_next_event();
		if(e.type == "Activated")
		{
			printf("Event: %s, source = %p \n", e.type.c_str(), e.source);

			//Prototypes
			for(unsigned int i = 0; i < root_widgets.size(); ++i)
			{
				if(root_widgets[i] == e.source)
				{
					interface::Widget* n = prototypes[i]->Clone();
					edit_widgets.push_back(n);

					interface::Widget_editor* widget_editor = new interface::Widget_editor;
					widget_editor->Set_widget(n);
					Attribute_groups::iterator ag = attribute_groups.find(e.source);
					if(ag != attribute_groups.end())
					{
						widget_editor->Add_attribute_group(attribute_groups[e.source]);
					}
					renderer->Add_widget(widget_editor);
					edit_interface->Add_widget(widget_editor);
					break;
				}
			}
			
			if(e.source == button_left)
			{
				inputbox->Set_alignment(interface::HALIGN_LEFT);
				button_center->Release();
				button_right->Release();
			}
			if(e.source == button_right)
			{
				inputbox->Set_alignment(interface::HALIGN_RIGHT);
				button_center->Release();
				button_left->Release();
			}
			if(e.source == button_center)
			{
				inputbox->Set_alignment(interface::HALIGN_CENTER);
				button_left->Release();
				button_right->Release();
			}
		}
	}
}

int main()
{
	al_init();
	al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 24, ALLEGRO_REQUIRE);
 	display = al_create_display(width, height);
 	if(!display)
 	{
 		printf("Failed to create display\n");
 		return 0;
	}
	
	ALLEGRO_EVENT_SOURCE time_event_source;
	al_init_user_event_source(&time_event_source);
	//ALLEGRO_EVENT_SOURCE *time_event_source = al_create_user_event_source();
	
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, &time_event_source);

	if(!Init())
		return 0;

	double last_time = al_current_time();

	bool quit = false;

	while(!quit)
	{
		double current_time = al_current_time();
		double dt = current_time - last_time;
		last_time = current_time;

		ALLEGRO_EVENT time_event;
		time_event.type = EVENT_UPDATE;
		interface::UPDATE_EVENT ue;
		ue.dt = dt;
		time_event.user.data1 = (intptr_t)(&ue);
		al_emit_user_event(&time_event_source, &time_event, NULL);
		

		ALLEGRO_EVENT event;
		while (al_get_next_event(event_queue, &event))
		{
		  	if (ALLEGRO_EVENT_KEY_DOWN == event.type)
			{
				if (ALLEGRO_KEY_ESCAPE == event.keyboard.keycode)
				{
//					quit = true;
				}
			}
			if (ALLEGRO_EVENT_DISPLAY_CLOSE == event.type)
			{
				quit = true;
			}
//	 		printf("Event type: %i\n", event.type);
			Event(event);
		}
		if (quit)
			break;

		Update(dt);

		al_clear_to_color(al_map_rgb(0, 0, 0));
		Render();
		al_flip_display();

		al_rest(0.001);
	}

	Shutdown();

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}
