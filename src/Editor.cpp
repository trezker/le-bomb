#include "Editor.h"
#include "Functions.h"
#include <cmath>
#include <iostream>
#include "Billboardnode.h"
#include "Quadnode.h"

ALLEGRO_BITMAP* bomb_texture;


Billboardnode* billboard = NULL;


Editor::Editor()
:camera(NULL)
,light(NULL)
,heightmap(NULL)
,move_forward(false)
,move_backward(false)
,move_left(false)
,move_right(false)
,move_up(false)
,move_down(false)
{
	fov = 45.f;
	near = 1.f;
	far = 1000.f;
	width = 640;
	height = 480;
}

Editor::~Editor()
{
	delete camera;
	delete light;
}

void Editor::Set_heightmap(Heightmap* h)
{
	if(heightmap)
		light->Detach_node(heightmap);
	heightmap = h;
	if(!h)
		return;
	light->Attach_node(h);
	camera->Set_position(Vector3(h->Get_width_x()/2, 1.5f, h->Get_width_z()/2));
}

void Editor::Init()
{
	camera = new Cameranode();
	camera->Set_position(Vector3(0, 1.5f, 0));
	camera->Set_rotation(Vector3(0, 0, 0));
	root.Attach_node(camera);

	light = new Lightnode;
	camera->Attach_node(light);
	
	billboard = new Billboardnode();
	billboard->Set_position(Vector3(5, 0, 5));
	light->Attach_node(billboard);

	bomb_texture = al_iio_load("media/bomb_sprite.png");
	Quadnode* quad = new Quadnode();
	quad->Set_texture(bomb_texture);
	billboard->Attach_node(quad);
}

void Editor::Update(double dt)
{
	Vector3 direction(move_right-move_left, 0, move_backward-move_forward);
	direction.Normalize();
	direction*=dt*10;
	float angle = camera->Get_rotation().y*3.14159f/180.f;
	Vector3 speed(direction.x*cos(-angle) + direction.z*sin(-angle),
					(move_up-move_down)*dt*10,
					direction.x*sin(angle) + direction.z*cos(angle));

	camera->Set_position(camera->Get_position()+speed);
	billboard->Update_vectors(camera->Get_position());

	ALLEGRO_MOUSE_STATE ret_state;
	al_get_mouse_state(&ret_state);
	if((ret_state.buttons&1))
	{
		Prerender_perspective_view(fov, width/height, near, far);
		Vector3 oglpoint = GetOGLPos(ret_state.x, ret_state.y, camera);
		Postrender_perspective_view();
		//Single point
/*		float h = heightmap->Get_height(oglpoint.x, oglpoint.z);
		heightmap->Set_height(oglpoint.x, oglpoint.z, h-.1*dt);
*/
		//Full circle
/*		Height_points height_points = heightmap->Get_height_points_in_circle(oglpoint.x, oglpoint.z, 10);
		for(Height_points::iterator i=height_points.begin(); i!=height_points.end(); ++i)
			heightmap->Set_height(i->x, i->y, i->height-.1*dt);
*/
		//Profile circle
		float curve[5] = {-1, -.7, 0, .3, 0};
		Height_points height_points = heightmap->Get_height_points_in_circle(oglpoint.x, oglpoint.z, 5);
		for(Height_points::iterator i=height_points.begin(); i!=height_points.end(); ++i)
		{
			float dx = i->x-oglpoint.x;
			float dy = i->y-oglpoint.z;
			float r = sqrt(dx*dx + dy*dy);
			int low = r;
			float p = r-low;
			float h = i->height+dt*((curve[low+1]-curve[low])*p+curve[low]);
			heightmap->Set_height(i->x, i->y, h);
		}
		heightmap->Recalc_normals();
	}
}

void Editor::Render()
{
	Prerender_perspective_view(fov, width/height, near, far);

	glEnable(GL_DEPTH_TEST);
 	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);

	root.Apply();

	glDisable(GL_LIGHTING);		// Disable Lighting
	Postrender_perspective_view();
}

void Editor::Event(ALLEGRO_EVENT event)
{
	if(ALLEGRO_EVENT_KEY_DOWN == event.type)
	{
		if(ALLEGRO_KEY_W == event.keyboard.keycode)
		{
			move_forward = true;
		}
		if(ALLEGRO_KEY_S == event.keyboard.keycode)
		{
			move_backward = true;
		}
		if(ALLEGRO_KEY_A == event.keyboard.keycode)
		{
			move_left = true;
		}
		if(ALLEGRO_KEY_D == event.keyboard.keycode)
		{
			move_right = true;
		}
		if(ALLEGRO_KEY_Q == event.keyboard.keycode)
		{
			move_up = true;
		}
		if(ALLEGRO_KEY_Z == event.keyboard.keycode)
		{
			move_down = true;
		}
	}
	if(ALLEGRO_EVENT_KEY_UP == event.type)
	{
		if(ALLEGRO_KEY_W == event.keyboard.keycode)
		{
			move_forward = false;
		}
		if(ALLEGRO_KEY_S == event.keyboard.keycode)
		{
			move_backward = false;
		}
		if(ALLEGRO_KEY_A == event.keyboard.keycode)
		{
			move_left = false;
		}
		if(ALLEGRO_KEY_D == event.keyboard.keycode)
		{
			move_right = false;
		}
		if(ALLEGRO_KEY_Q == event.keyboard.keycode)
		{
			move_up = false;
		}
		if(ALLEGRO_KEY_Z == event.keyboard.keycode)
		{
			move_down = false;
		}
	}
	if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
//			printf("Event: x: %i y: %i dx: %i dy %i\n", event.mouse.x, event.mouse.y, event.mouse.dx, event.mouse.dy);
		ALLEGRO_MOUSE_STATE ret_state;
		al_get_mouse_state(&ret_state);

		if((ret_state.buttons&2))// && ((event.mouse.x != width/2) || (event.mouse.y != height/2)))
		{
			camera->Set_rotation(camera->Get_rotation()+Vector3(event.mouse.dy, event.mouse.dx, 0));
			al_set_mouse_xy(width/2, height/2);
		}
	}
}
