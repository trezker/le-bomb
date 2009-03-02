#include "Game.h"
#include <iostream>
#include <cmath>
#include <Scenenode.h>
#include <Transformnode.h>
#include <Heightmap.h>
#include <Cameranode.h>
#include <Lightnode.h>
#include <GL/glu.h>
#include "Editor.h"
#include "Functions.h"
#include "Play.h"

int width = 640;
int height = 480;

Heightmap* heightmap = NULL;
Editor editor;
Play play;

Game::Game()
:quit(false)
,gamestate(NULL)
{
}


Game::~Game()
{
}

void Game::Run()
{
	al_init();
	al_install_mouse();
	al_install_keyboard();
	al_iio_init();
	al_font_init();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
	display = al_create_display(width, height);

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)al_get_keyboard());
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)al_get_mouse());

	Init();

	double last_time = al_current_time();

	while(1)
	{
		if (quit)
			break;
		ALLEGRO_EVENT event;
		if (al_get_next_event(event_queue, &event))
		{
		  	if (ALLEGRO_EVENT_KEY_DOWN == event.type)
			{
				if (ALLEGRO_KEY_ESCAPE == event.keyboard.keycode)
				{
					break;
				}
			}
			if (ALLEGRO_EVENT_DISPLAY_CLOSE == event.type)
			{
				break;
			}
			Event(event);
		}

		double current_time = al_current_time();
		double dt = current_time - last_time;
		last_time = current_time;
		Update(dt);

		al_clear(al_map_rgb(0, 0, 0));
		Render();
		al_flip_display();

		al_rest(0.001);
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}

void Game::Init()
{
	heightmap = new Heightmap();

	editor.Init();
	editor.Set_heightmap(heightmap);
	
	play.Init();
	play.Set_heightmap(heightmap);
	gamestate = &play;
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
			gamestate = &editor;
		}
		if (ALLEGRO_KEY_2 == event.keyboard.keycode)
		{
			gamestate = &play;
		}
	}
	gamestate->Event(event);
}
