#include "Bomb.h"
#include "Net.h"

Bomb::Bomb()
:net_node(NULL)
,deleteme(false)
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
	Process_net_events();
}

bool Bomb::Exploded()
{
	return timeout<=0;
}

float Bomb::Damage_at(Vector3 p)
{
	float range = 5;
	float damage = 10;
	float r = (p-Get_position()).Length();
	if(r>range)
		return 0;
	return (range-r)/range*damage;
}

void Bomb::Register_net_node(ZCom_Control *control, ZCom_ClassID class_id)
{
	net_node = new ZCom_Node;
	net_node->registerNodeDynamic(class_id, control);

	ZCom_BitStream *adata = new ZCom_BitStream();
	Vector3 pos = Get_position();
	adata->addFloat(pos.x, POSITION_MANTISSA);
	adata->addFloat(pos.y, POSITION_MANTISSA);
	adata->addFloat(pos.z, POSITION_MANTISSA);
	net_node->setAnnounceData(adata);
}

void Bomb::Process_net_events()
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
	}
}

bool Bomb::Deleteme()
{
	return deleteme;
}
