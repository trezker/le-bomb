#include "Player.h"

Player::Player()
:move_forward(false)
,move_backward(false)
,move_left(false)
,move_right(false)
,move_up(false)
,move_down(false)
{
	transform = new Transformnode();
	Attach_node(transform);
	model = new Modelnode;
	model->Loadmodel("media/darwinian.raw");
	transform->Attach_node(model);
}

Player::~Player()
{
	delete transform;
	delete model;
//	delete net_node;
}

void Player::Set_position(Vector3 p)
{
	transform->Set_position(p);
}

Vector3 Player::Get_position()
{
	return transform->Get_position();
}

void Player::Set_texture(ALLEGRO_BITMAP* t)
{
	model->Set_texture(t);
}

void Player::Update(double dt, Vector3 camera_right, Vector3 camera_front, Heightmap* heightmap)
{
	Vector3 direction(move_left-move_right, move_up-move_down, move_forward-move_backward);
	direction.Normalize();

	Vector3 right = camera_right;
	right.y = 0;
	right.Normalize();
	Vector3 front = camera_front;
	front.y = 0;
	front.Normalize();

	Vector3 speed;
	speed += right*direction.x;
	speed += Vector3(0, 1, 0)*direction.y;
	speed += front*direction.z;
	
	Vector3 newpos = Get_position()+speed*10*dt;
	newpos.y = heightmap->Get_height(newpos.x, newpos.z);
	Set_position(newpos);
}

void Player::Event(ALLEGRO_EVENT event)
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
}
