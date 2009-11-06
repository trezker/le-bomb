#include "Play.h"
#include "Functions.h"
#include <cmath>
#include <iostream>
#include "scenegraph/Billboardnode.h"
#include "scenegraph/Quadnode.h"
#include "scenegraph/Modelnode.h"
#include "Net.h"
#include <allegro5/allegro_primitives.h>
#include <cstdio>

Play::Play()
:camera(NULL)
,light(NULL)
,heightmap(NULL)
,font(NULL)
,player(NULL)
,server(NULL)
,client(NULL)
,netconf(NULL)

{
	fov = 45.f;
	near = 1.f;
	far = 1000.f;
	width = 640;
	height = 480;

	camera_distance = 20;
	camera_elevation = 5;
}

Play::~Play()
{
	delete camera;
	delete light;
	delete client;
	delete server;
	al_save_config_file(netconf, "net.cfg");
	al_destroy_config(netconf);
}

void Play::Init()
{
	netconf = al_load_config_file("net.cfg");
	if(!netconf)
	{
		netconf = al_create_config();
	}
	
	font = al_load_ttf_font("media/DejaVuSans.ttf", 20, 0);

	camera = new Cameranode();
	camera->Set_position(Vector3(0, 1.5f, 0));
	camera->Set_rotation(Vector3(0, 0, 0));
	root.Attach_node(camera);

	light = new Lightnode;
	camera->Attach_node(light);

	bomb_texture = al_load_bitmap("media/bomb_sprite.png");
//	darwinian_texture = al_iio_load("media/darwinian.png");
	darwinian_texture = al_load_bitmap("media/darwinian_textured.png");
	heightmap_texture = al_load_bitmap("media/grass.png");

	Add_heightmap(new Heightmap);

	player = new Player();	
	player->Set_position(Vector3(15, 0, 10));
//	player->Set_texture(darwinian_texture);
	light->Attach_node(player);
}

void Play::Update(double dt)
{
	if ( server )
	{
		server->Update(dt);
		server->ZCom_processInput();
		server->ZCom_processOutput();
	}
	if(client)
	{
		client->Update(dt);
		client->ZCom_processInput();
		client->ZCom_processOutput();
		if(client->Disconnected())
		{
			delete client;
			client=NULL;
		}
	}

	heightmap->Process_net_events();

	if(player)
		player->Update(dt, camera->Get_right(), camera->Get_front(), heightmap);

	for(Players::iterator i = players.begin(); i != players.end(); )
	{
		(*i)->Update(dt, camera->Get_right(), camera->Get_front(), heightmap);
		if((*i)->Deleteme())
		{
			light->Detach_node(*i);
			delete *i;
			i=players.erase(i);
		}
		else
		{
			++i;
		}
	}

	camera->Look_at(player->Get_position()+Vector3(0, 2, 0));
	Vector3 camera_position = camera->Get_position();
	Vector3 player_position = player->Get_position();
	float height_adjust = heightmap->Get_height(camera_position.x, camera_position.z)-camera_position.y;
	height_adjust+=camera_elevation;
//	float player_height = player_position.y;
	camera_position.y = 0;
	player_position.y = 0;
	Vector3 adjust;
	if((camera_position-player_position).Length()>camera_distance+1)
	{
		adjust = camera->Get_front();
		adjust.y = 0;
	}
	if((camera_position-player_position).Length()<camera_distance)
	{
		adjust = -camera->Get_front();
		adjust.y = 0;
	}
	adjust.y=height_adjust;
	camera->Set_position(camera->Get_position()+adjust*dt*20);

	for(Bombs::iterator i = bombs.begin(); i != bombs.end(); )
	{
		(*i)->Update(dt, camera->Get_position());
//		if((*i)->Exploded())
		if((*i)->Deleteme())
		{
			Vector3 point = (*i)->Get_position();
			float curve[5] = {-1, -.7, 0, .3, 0};
			heightmap->Apply_brush(point.x, point.z, 10, 1, curve, 5);
			light->Detach_node(*i);
			delete *i;
			i=bombs.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void Play::Render()
{
	Prerender_perspective_view(fov, width/height, near, far);

	glEnable(GL_DEPTH_TEST);
 	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);

	root.Apply();

	glDisable(GL_LIGHTING);		// Disable Lighting
	glDisable(GL_DEPTH_TEST);
	Postrender_perspective_view();

	if(player)
	{
		al_draw_filled_rectangle(10, 10, 10+player->Get_health(), 30, al_map_rgb(255, 0, 0));
		al_draw_textf(font, 10, 40, 0, "Score: %d", player->Get_score());
	}
}

void Play::Event(ALLEGRO_EVENT event)
{
	if(player)
		player->Event(event);

	if(ALLEGRO_EVENT_KEY_DOWN == event.type)
	{
		if(ALLEGRO_KEY_SPACE == event.keyboard.keycode)
		{
/*			Bomb* bomb = new Bomb;
			bomb->Set_position(Vector3(player->Get_position()));
			bomb->Set_texture(bomb_texture);
			bomb->Set_timeout(2);
			bombs.push_back(bomb);
			light->Attach_node(bomb);
*/			
			if(client && client->Ready() && player)
			{
				ZCom_BitStream *packet = new ZCom_BitStream();
				packet->addInt(CREATE_BOMB, PACKET_TYPE_SIZE);
				client->Send_data(packet);
				player->Drop_bomb();
			}
		}
		if(ALLEGRO_KEY_F5 == event.keyboard.keycode)
		{
			if(!server)
			{
				server = new Server();
				server->ZCom_setDebugName("Server");
				server->Register_classes();
				const char *port_str = al_get_config_value(netconf, "server", "port");
				int port=0;
				if(port_str)
				{
					port=atoi(port_str);
				}
				if(port==0)
				{
					al_set_config_value(netconf, "server", "port", "10000");
					port = 10000;
				}
				bool result = server->ZCom_initSockets(true, port, 0);
				if (!result)
				{
					delete server;
					server = NULL;
					printf("Server failed initializing\n");
				}
				server->Init();
			}
		}
		if(ALLEGRO_KEY_F8 == event.keyboard.keycode)
		{
			if(!client)
			{
				client = new Client();
				client->ZCom_setDebugName("Client");
				client->Register_classes();
				client->Set_play(this);
				// this creates and initializes the network sockets
				// true = use udp socket, 0 = let OS choose UDP port, 0 = no internal socket
				bool result = client->ZCom_initSockets(true, 0, 0);
				// if result is false, Zoidcom had problems while initializing
				if (!result)
				{
					delete client;
					client = NULL;
					printf("Client failed initializing\n");
				}
				// put this into a codeblock so that server_addr gets out of scope before 
				// 'delete zcom;' get called (everything needs to be gone before the 
				// ZoidCom object gets deleted)
				else
				{
					const char *server_str = al_get_config_value(netconf, "client", "server");
					if(!server_str)
					{
						al_set_config_value(netconf, "client", "server", "localhost:10000");
						server_str = "localhost:10000";
					}

					// prepare the destination adress
					ZCom_Address server_addr;
//					server_addr.setAddress( eZCom_AddressUDP, 0, "localhost:10000");
					server_addr.setAddress( eZCom_AddressUDP, 0, server_str);
					// and connect
					ZCom_ConnID connection_id = client->ZCom_Connect(server_addr, NULL);

					// unable to connect
					// this happens if the connection process can't even be started
					// for some reason
					if (connection_id == ZCom_Invalid_ID)
					{
						delete client;
						client = NULL;
						printf("Client failed connection\n");
					}
				}
			}

		}
	}
	if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
//			printf("Event: x: %i y: %i dx: %i dy %i\n", event.mouse.x, event.mouse.y, event.mouse.dx, event.mouse.dy);
		ALLEGRO_MOUSE_STATE ret_state;
		al_get_mouse_state(&ret_state);

		if((ret_state.buttons&2))// && ((event.mouse.x != width/2) || (event.mouse.y != height/2)))
		{
//			camera->Set_rotation(camera->Get_rotation()+Vector3(event.mouse.dy, event.mouse.dx, 0));
			camera_elevation += event.mouse.dy/10.f;
			if(camera_elevation<2)
				camera_elevation = 2;
			camera->Set_position(camera->Get_position()+camera->Get_right()*event.mouse.dx);
			al_set_mouse_xy(width/2, height/2);
		}

		camera_distance -= event.mouse.dz;
		if(camera_distance<0)
			camera_distance = 0;
	}
}

void Play::Add_heightmap(Heightmap* h)
{
	if(heightmap)
	{
		light->Detach_node(heightmap);
		delete heightmap;
	}
	heightmap = h;
	camera->Set_position(Vector3(h->Get_width_x()/2, camera_elevation, 0));
	heightmap->Set_texture(heightmap_texture);
	light->Attach_node(heightmap);
}

void Play::Add_bomb(Bomb* bomb)
{
	bomb->Set_texture(bomb_texture);
	light->Attach_node(bomb);
	bombs.push_back(bomb);
}

void Play::Add_player(Player* p, bool owner)
{
	if(owner)
	{
		if(player)
		{
			light->Detach_node(player);
			delete player;
		}
		player = p;
	}
	else
	{
		players.push_back(p);
	}
	p->Set_texture(darwinian_texture);
	light->Attach_node(p);
}
