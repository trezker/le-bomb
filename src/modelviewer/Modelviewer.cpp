#include <allegro5/allegro5.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
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

#include "scenegraph/Transformnode.h"
#include "scenegraph/Modelnode.h"
#include "scenegraph/Scenenode.h"
#include "scenegraph/Cameranode.h"
#include "scenegraph/Lightnode.h"

#include <GL/glu.h>

#include <cstdio>

interface::Renderer* renderer = NULL;
interface::Group* root_interface;

interface::Button* load_button;
interface::Label* filename_label;

interface::Spinbox* rotate_y_spinbox;

interface::Event_queue event_queue;
ALLEGRO_FONT* font = NULL;

int width = 800;
int height = 600;

Transformnode* transform;
Modelnode* model;
Cameranode* camera;
Lightnode* light;
Scenenode root;

float rotate_y = 0;

ALLEGRO_BITMAP* texture;

bool Init()
{
	interface::Add_event_queue(&event_queue);

	renderer = new interface::Renderer();
	interface::Set_renderer(renderer);
	font = al_load_ttf_font("media/DejaVuSans.ttf", -12, 0);
	renderer->Set_font(font);

	//Load
	load_button = new interface::Button;
	load_button->Set_bounding_rect(interface::Rect(0, 0, 100, 20));
	load_button->Set_text("Load");

	filename_label = new interface::Label;
	filename_label->Set_bounding_rect(interface::Rect(0, 30, 100, 20));
	filename_label->Set_text("No model loaded");
	
	rotate_y_spinbox = new interface::Spinbox;
	rotate_y_spinbox->Set_bounding_rect(interface::Rect(0, 60, 100, 20));
	rotate_y_spinbox->Set_stepsize(.1);

	root_interface = new interface::Group();
	renderer->Add_widget(root_interface);
	root_interface->Add_widget(load_button);
	root_interface->Add_widget(filename_label);
	root_interface->Add_widget(rotate_y_spinbox);


	camera = new Cameranode();
	camera->Set_rotate_around_world_origo(true);
	camera->Set_position(Vector3(0, 1.5f, 5));
	camera->Set_rotation(Vector3(0, 0, 0));
	root.Attach_node(camera);

	light = new Lightnode;
	camera->Attach_node(light);

	transform = new Transformnode();
	transform->Set_position(Vector3(0, 0, 0));
	light->Attach_node(transform);
	model = NULL;

	texture = al_load_bitmap("media/darwinian_textured.png");

	model = new Modelnode;
//	model->Loadmodel("media/darwinian_textured.tmf");
	transform->Attach_node(model);

	model->Set_texture(texture);

	return true;
}

void Shutdown()
{
	delete renderer;
	renderer = NULL;
	interface::Set_renderer(NULL);
}

void Update(double dt)
{
	Vector3 rot = transform->Get_rotation();
	rot.y += rotate_y;
	transform->Set_rotation(rot);
}

void Prerender_perspective_view(float fov, float aspect, float near, float far)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(fov, aspect, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Postrender_perspective_view()
{
	//Return to Allegros 2D world
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Render()
{
	Prerender_perspective_view(90, width/height, 1, 100);

	glEnable(GL_DEPTH_TEST);
 	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);

	root.Apply();

	glDisable(GL_LIGHTING);		// Disable Lighting
	glDisable(GL_DEPTH_TEST);
	Postrender_perspective_view();

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
			if(e.source == load_button)
			{
				ALLEGRO_NATIVE_DIALOG *file_chooser = al_create_native_file_dialog(
					al_create_path("./media/"), "Choose model to load", ".;tmf", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
				al_show_native_file_dialog(file_chooser);
				if(al_get_native_file_dialog_count(file_chooser) != 0)
				{
					const ALLEGRO_PATH *path = al_get_native_file_dialog_path(file_chooser, 0);
					const char *char_path = al_path_cstr(path, '/');
					filename_label->Set_text(char_path);

					model->Loadmodel(char_path);
				}
				al_destroy_native_dialog(file_chooser);
			}
		}
	}
	
	rotate_y = rotate_y_spinbox->Get_value();

	ALLEGRO_MOUSE_STATE mouse_state;
	al_get_mouse_state(&mouse_state);
	bool lmb = al_mouse_button_down(&mouse_state, 1);

	ALLEGRO_KEYBOARD_STATE keyboard_state;
	al_get_keyboard_state(&keyboard_state);
	
	if (ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
		if(lmb)
		{
			Vector3 rot = camera->Get_rotation();
			if(!al_key_down(&keyboard_state, ALLEGRO_KEY_X))
				rot.y += event.mouse.dx;
			if(!al_key_down(&keyboard_state, ALLEGRO_KEY_Y))
				rot.x += event.mouse.dy;
			camera->Set_rotation(rot);
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
//	ALLEGRO_EVENT_SOURCE *time_event_source = al_create_user_event_source();
	
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
