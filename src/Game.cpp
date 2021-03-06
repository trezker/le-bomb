#include "Game.h"
#include <iostream>
#include <cmath>
#include "Heightmap.h"
#include "scenegraph/Scenenode.h"
#include "scenegraph/Transformnode.h"
#include "scenegraph/Cameranode.h"
#include "scenegraph/Lightnode.h"
#include <GL/glu.h>
#include "Functions.h"

int width = 640;
int height = 480;

Heightmap* heightmap = NULL;

Game::Game()
:quit(false)
,gamestate(NULL)
,zcom(NULL)
{
}


Game::~Game()
{
	delete editor;
	delete play;
	delete zcom;
}

void Game::Run()
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
 		std::cout<<"Failed to create display"<<std::endl;
 		return;
	}

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	if(!Init())
		return;

	double last_time = al_current_time();

	while(1)
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

		al_clear_to_color(al_map_rgb(0, 0, 0));
		Render();
		al_flip_display();

		al_rest(0.001);
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}

bool Game::Init()
{
	zcom = new ZoidCom();
	if (!zcom || !zcom->Init())
	{
		std::cout<<"Zoidcom init failed"<<std::endl;
		return false;
	}

	heightmap = new Heightmap();

	editor = new Editor;
	editor->Init();
	editor->Set_heightmap(heightmap);
	
	play = new Play;
	play->Init();
	gamestate = play;
	return true;
}

void Game::Update(double dt)
{
	gamestate->Update(dt);
}

void Game::Render()
{
	gamestate->Render();
}

void Game::Event(ALLEGRO_EVENT event)
{
	if (ALLEGRO_EVENT_KEY_UP == event.type)
	{
		if (ALLEGRO_KEY_1 == event.keyboard.keycode)
		{
			gamestate = editor;
		}
		if (ALLEGRO_KEY_2 == event.keyboard.keycode)
		{
			gamestate = play;
		}
	}
	gamestate->Event(event);
}
