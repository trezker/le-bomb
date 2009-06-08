#include "Player.h"
#include "Net.h"
#include <cmath>

Player::Player()
:fallspeed(0)
,move_forward(false)
,move_backward(false)
,move_left(false)
,move_right(false)
,move_up(false)
,move_down(false)
,health(100)
,score(0)
,dropping_bomb(false)
,net_node(NULL)
,deleteme(false)
{
	transform = new Transformnode();
	Attach_node(transform);
/*	model = new Modelnode;
//	model->Loadmodel("media/darwinian.raw");
	model->Loadmodel("media/darwinian_textured.tmf");
*/
	model = new Animated_modelnode;
	model->Load_model("media/darw.md5mesh");
	model->Load_animation("media/darw_drop.md5anim", "drop");
	model->Load_animation("media/darw_walk.md5anim", "walk");
	model->Play_animation("walk", true);
	transform->Attach_node(model);
}

Player::~Player()
{
	delete transform;
	delete model;
	delete net_node;
}

void Player::Set_position(Vector3 p)
{
	position = p;
	transform->Set_position(position);
}

Vector3 Player::Get_position()
{
	return position;
}

void Player::Set_texture(ALLEGRO_BITMAP* t)
{
	model->Set_texture(t);
}

void Player::Update(double dt, Vector3 camera_right, Vector3 camera_front, Heightmap* heightmap)
{
	Process_net_events();

	model->Update(dt);
	if(dropping_bomb && model->Animation_has_ended())
	{
		model->Play_animation("walk", true);
		dropping_bomb = false;
	}

	Vector3 direction(move_left-move_right, 0/*move_up-move_down*/, move_forward-move_backward);
	direction.Normalize();

	Vector3 right = camera_right;
	right.y = 0;
	right.Normalize();
	Vector3 front = camera_front;
	front.y = 0;
	front.Normalize();

	float speed_factor = 10*dt;
	Vector3 speed;
	speed += right*direction.x;
//	speed += Vector3(0, 1, 0)*direction.y;
	speed += front*direction.z;

	if(speed != Vector3::ZERO)
	{
		float angle = atan2(speed.x, speed.z)*180/M_PI;
		transform->Set_rotation(Vector3(0, angle, 0));
		Vector3 map_normal = heightmap->Get_normal(Get_position().x, Get_position().z);
		map_normal.y = 0;
		if(Get_position().y<=heightmap->Get_height(Get_position().x, Get_position().z))
		{
			speed += map_normal*1.1;
		}
		model->Pause_animation(false);
	}
	else
	{
		if(!dropping_bomb)
			model->Pause_animation(true);
	}
	
	Vector3 newpos = Get_position()+speed*speed_factor;
	if(heightmap->Contains(newpos.x, newpos.z))
	{
		float mapheight = heightmap->Get_height(newpos.x, newpos.z);
		if(newpos.y>mapheight)
		{
			fallspeed -= 20*dt;
			newpos.y += fallspeed*dt;
		}
		if(newpos.y<mapheight)
		{
			fallspeed = 0;
			newpos.y = mapheight;
		}
		Set_position(newpos);
	}
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

void Player::Damage(float d)
{
	health-=d;
}

void Player::Set_health(float h)
{
	health = h;
}

float Player::Get_health()
{
	return health;
}

void Player::Add_score(int s)
{
	score += s;
}

int Player::Get_score()
{
	return score;
}

void Player::Drop_bomb()
{
	model->Play_animation("drop", false);
	model->Pause_animation(false);
	dropping_bomb = true;
}


ZCom_Node* Player::Register_net_node(ZCom_Control *control, ZCom_ClassID class_id)
{
	net_node = new ZCom_Node;

	ZCom_BitStream *adata = new ZCom_BitStream();
	Vector3 pos = Get_position();
	adata->addFloat(pos.x, POSITION_MANTISSA);
	adata->addFloat(pos.y, POSITION_MANTISSA);
	adata->addFloat(pos.z, POSITION_MANTISSA);
	net_node->setAnnounceData(adata);

	net_node->beginReplicationSetup(5);
	net_node->addReplicationFloat(&health, 10, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL);
	net_node->addReplicationInt(&score, 10, false, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL);

	net_node->addInterpolationFloat(&position.x, 10, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_PROXY|ZCOM_REPRULE_OWNER_2_AUTH, 1, &interpos.x);
	net_node->addInterpolationFloat(&position.y, 10, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_PROXY|ZCOM_REPRULE_OWNER_2_AUTH, 1, &interpos.y);
	net_node->addInterpolationFloat(&position.z, 10, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_PROXY|ZCOM_REPRULE_OWNER_2_AUTH, 1, &interpos.z);
/*
	net_node->addReplicationFloat(&position.x, 10, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_PROXY|ZCOM_REPRULE_OWNER_2_AUTH);
	net_node->addReplicationFloat(&position.y, 10, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_PROXY|ZCOM_REPRULE_OWNER_2_AUTH);
	net_node->addReplicationFloat(&position.z, 10, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_PROXY|ZCOM_REPRULE_OWNER_2_AUTH);
*/	net_node->endReplicationSetup();

	net_node->registerNodeDynamic(class_id, control);
	return net_node;
}

ZCom_Node* Player::Get_net_node()
{
	return net_node;
}

void Player::Process_net_events()
{
	if(!net_node)
		return;
	// checkEventWaiting() returns true whenever there is a waiting event in the node
	while (net_node->checkEventWaiting()) 
	{
		eZCom_Event       type;            // event type
		eZCom_NodeRole    remote_role;     // role of remote sender
		ZCom_ConnID       conn_id;         // connection id of sender

		// get next waiting event
		ZCom_BitStream *data = net_node->getNextEvent(&type, &remote_role, &conn_id);

		// the server object has been deleted on the server, we should delete it here, too
		if (remote_role == eZCom_RoleAuthority && type == eZCom_EventRemoved)
			deleteme = true;

		if (remote_role == eZCom_RoleAuthority && type == eZCom_EventUser)
		{
			int packet_type = data->getInt(PACKET_TYPE_SIZE);
			switch(packet_type)
			{
				case PLAYER_KILLED:
				{
					float x = data->getFloat(POSITION_MANTISSA);
					float y = data->getFloat(POSITION_MANTISSA);
					float z = data->getFloat(POSITION_MANTISSA);
					Set_position(Vector3(x, y, z));
					break;
				}
			}
		}
	}
}

bool Player::Deleteme()
{
	return deleteme;
}
