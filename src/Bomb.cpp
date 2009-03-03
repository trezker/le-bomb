#include "Bomb.h"

Bomb::Bomb()
{
	billboard = new Billboardnode;
	Attach_node(billboard);
	quad = new Quadnode;
	Vector3 p[4];
	p[0].Set(-.5, 0, 0);
	p[1].Set(+.5, 0, 0);
	p[2].Set(+.5, 1, 0);
	p[3].Set(-.5, 1, 0);
	quad->Set_corners(p);
	billboard->Attach_node(quad);
	timeout = 0;
}

Bomb::~Bomb()
{
	delete quad;
	delete billboard;
	delete net_node;
}

void Bomb::Set_position(Vector3 p)
{
	billboard->Set_position(p);
}

Vector3 Bomb::Get_position()
{
	return billboard->Get_position();
}

void Bomb::Set_timeout(float t)
{
	timeout = t;
}

void Bomb::Set_texture(ALLEGRO_BITMAP* t)
{
	quad->Set_texture(t);
}

void Bomb::Update(double dt, Vector3 cam)
{
	timeout-=dt;
	billboard->Update_vectors(cam);
}

bool Bomb::Exploded()
{
	return timeout<=0;
}
/*
ZCom_ClassID Bomb::server_id = 0;
ZCom_ClassID Bomb::client_id = 0;
ZCom_ClassID Bomb::Get_net_class_id(bool server)
{
	if(server)
		return server_id;
	else
		return client_id;
}
*/
void Bomb::Register_net_node(ZCom_Control *control, ZCom_ClassID class_id)
{
	net_node = new ZCom_Node;
	net_node->registerNodeDynamic(class_id, control);
}
