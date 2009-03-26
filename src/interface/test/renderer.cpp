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
#include "interface/Inputbox.h"
#include "interface/Widget_editor.h"
#include "interface/Group.h"

interface::Renderer* renderer = NULL;
interface::Group* root_interface;
interface::Group* edit_interface;

typedef std::vector<interface::Widget*> Widgets;
Widgets root_widgets;
Widgets edit_widgets;
Widgets editor_prototypes;
Widgets prototypes;

class Button_editor: public interface::Widget_editor
{
public:
	Button_editor();
private:
};

//interface::Button* button;
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
	font = al_ttf_load_font("media/DejaVuSans.ttf", -12, 0);
	renderer->Set_font(font);


	//Button
	interface::Button* button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 0, 100, 20));
	button->Set_label("Button");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Button* button_prototype = new interface::Button;
	button_prototype->Set_bounding_rect(interface::Rect(100, 0, 100, 20));
	button_prototype->Set_label("Button");
	prototypes.push_back(button_prototype);

	//Label
	button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 20, 100, 20));
	button->Set_label("Label");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Label* label_prototype = new interface::Label;
	label_prototype->Set_bounding_rect(interface::Rect(100, 0, 100, 20));
	label_prototype->Set_text("Label");
	prototypes.push_back(label_prototype);

	//Inputbox
	button = new interface::Button;
	button->Set_bounding_rect(interface::Rect(0, 40, 100, 20));
	button->Set_label("Inputbox");
	renderer->Add_widget(button);
	root_widgets.push_back(button);

	interface::Inputbox* inputbox_prototype = new interface::Inputbox;
	inputbox_prototype->Set_bounding_rect(interface::Rect(100, 0, 100, 20));
	inputbox_prototype->Set_text("Inputbox");
	prototypes.push_back(inputbox_prototype);

	root_interface = new interface::Group;
	root_interface->Set_bounding_rect(interface::Rect(0, 0, width, height));
	edit_interface = new interface::Group;
	edit_interface->Set_bounding_rect(interface::Rect(100, 0, width-100, height));
	root_interface->Add_widget(edit_interface);

	for(Widgets::iterator i = root_widgets.begin(); i != root_widgets.end(); ++i)
		root_interface->Add_widget(*i);

	interface::Inputbox* inputbox = new interface::Inputbox;
	inputbox->Set_bounding_rect(interface::Rect(100, 100, 100, 20));
	inputbox->Set_text("Inputbox");
	renderer->Add_widget(inputbox);
	root_interface->Add_widget(inputbox);

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
//					quit = true;
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
