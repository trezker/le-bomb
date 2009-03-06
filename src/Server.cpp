#include "Server.h"
#include <iostream>
#include "Net.h"

Server::Server()
:heightmap(NULL)
{
}

Server::~Server()
{
	delete heightmap;
}

void Server::Init()
{
	heightmap = new Heightmap;
	heightmap->Register_net_node(this, heightmap_id);
}

void Server::Register_classes()
{
	heightmap_id = ZCom_registerClass("Heightmap");
	bomb_id = ZCom_registerClass("Bomb", ZCOM_CLASSFLAG_ANNOUNCEDATA);
	player_id = ZCom_registerClass("Player", ZCOM_CLASSFLAG_ANNOUNCEDATA);
}

void Server::Update(double dt)
{
	for(Bombs::iterator i = bombs.begin(); i != bombs.end(); )
	{
		(*i)->Update(dt, Vector3());
		if((*i)->Exploded())
		{
/*			Vector3 point = (*i)->Get_position();
			float curve[5] = {-1, -.7, 0, .3, 0};
			heightmap->Apply_brush(point.x, point.z, 10, 3, curve, 5);
*/			delete *i;
			i=bombs.erase(i);
			printf("Server: Bomb erased\n");
		}
		else
		{
			++i;
		}
	}
}

void Server::ZCom_cbDataReceived(ZCom_ConnID  _id, ZCom_BitStream &_data) {
	// read 4 bit integer
	int packet_type = _data.getInt(PACKET_TYPE_SIZE);
	switch(packet_type)
	{
		case CREATE_BOMB:
			printf("The client requested bomb creation.\n");
			float x = _data.getFloat(POSITION_MANTISSA);
			float y = _data.getFloat(POSITION_MANTISSA);
			float z = _data.getFloat(POSITION_MANTISSA);

			Bomb* bomb = new Bomb;
			bomb->Set_timeout(2);
			bomb->Set_position(Vector3(x, y, z));
			bomb->Register_net_node(this, bomb_id);
			bombs.push_back(bomb);
			break;
	}
}

bool Server::ZCom_cbConnectionRequest(ZCom_ConnID  _id, ZCom_BitStream &_request, ZCom_BitStream &_reply )
{
	printf("A client requested connection - the new id is [%d].\n", _id);
	return true;
}

// someone has connected
void Server::ZCom_cbConnectionSpawned( ZCom_ConnID _id )
{
	printf("New connection with id [%d]\n", _id);
}

// someone has disconnected
void Server::ZCom_cbConnectionClosed( ZCom_ConnID _id, eZCom_CloseReason _reason, ZCom_BitStream &_reasondata )
{
	printf("Connection with id [%d] closed\n", _id);
}

bool Server::ZCom_cbZoidRequest( ZCom_ConnID _id, zU8 _requested_level, ZCom_BitStream &_reason )
{
	// return true to grant the request, or false to deny it
	if (_requested_level == 1)
	{
		Player* player = new Player;
//		bomb->Set_position(Vector3(x, y, z));
		ZCom_Node* node = player->Register_net_node(this, player_id);
		node->setOwner(_id, true);
		players.push_back(player);
		return true;
	}
	else
		return false;
}
