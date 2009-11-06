#include "Client.h"
#include <iostream>
#include "Bomb.h"
#include "Net.h"
#include "Play.h"
#include "Heightmap.h"
#include <cstdio>

Client::Client()
:ready(false)
,disconnected(false)
,play(NULL)
{}

Client::~Client()
{
	ZCom_disconnectAll(NULL);
	printf("Disconnecting Client\n");
	double start_time = al_current_time();
	while(al_current_time()-start_time < 1)
	{
		ZCom_processInput();
		ZCom_processOutput();
	}
}

void Client::Update(double dt)
{
	ZCom_processReplicators(dt);
}

void Client::Set_play(Play* p)
{
	play = p;
}

void Client::Register_classes()
{
	heightmap_id = ZCom_registerClass("Heightmap");
	bomb_id = ZCom_registerClass("Bomb", ZCOM_CLASSFLAG_ANNOUNCEDATA);
	player_id = ZCom_registerClass("Player", ZCOM_CLASSFLAG_ANNOUNCEDATA);
}

void Client::Send_data(ZCom_BitStream *message)
{
	ZCom_sendData(server_id, message);
}

bool Client::Ready()
{
	return ready;
}

bool Client::Disconnected()
{
	return disconnected;
}

void Client::ZCom_cbConnectResult( ZCom_ConnID _id, eZCom_ConnectResult _result, ZCom_BitStream &_reply )
{
	if (_result == eZCom_ConnAccepted)
	{
		printf("Connection established. \n");
		ZCom_requestZoidMode(_id, 1);
		server_id = _id;
	}
	else
		printf("Connection failed\n");
}

void Client::ZCom_cbConnectionClosed( ZCom_ConnID _id, eZCom_CloseReason _reason, ZCom_BitStream &_reasondata )
{
	printf("Connection to server closed. ");
	if(_reason == eZCom_ClosedDisconnect)
		printf("Disconnect\n");
	if(_reason == eZCom_ClosedTimeout )
		printf("Timeout\n");
	if(_reason == eZCom_ClosedReconnect)
		printf("Reconnect\n");
	disconnected = true;
}

void Client::ZCom_cbZoidResult( ZCom_ConnID _id, eZCom_ZoidResult _result, zU8 _new_level, ZCom_BitStream & _reason )
{
	if (_result == eZCom_ZoidEnabled)
	{
		printf("Zoidlevel %d entered\n", _new_level);
		ready = true;
	}
	else
	{
		printf("Failed entering Zoidlevel %d\n", _new_level);
		disconnected = true;
	}
}

void Client::ZCom_cbNodeRequest_Dynamic( ZCom_ConnID _id, ZCom_ClassID _requested_class, ZCom_BitStream *_announcedata, eZCom_NodeRole _role, ZCom_NodeID _net_id ) 
{
	if (_requested_class == bomb_id) 
	{
		printf("Client: Bomb requested\n");
		float x = _announcedata->getFloat(POSITION_MANTISSA);
		float y = _announcedata->getFloat(POSITION_MANTISSA);
		float z = _announcedata->getFloat(POSITION_MANTISSA);
		Bomb* bomb = new Bomb;
		bomb->Register_net_node(this, bomb_id);
		bomb->Set_position(Vector3(x, y, z));
		play->Add_bomb(bomb);
	}
	if (_requested_class == player_id) 
	{
		printf("Client: Player requested\n");
		float x = _announcedata->getFloat(POSITION_MANTISSA);
		float y = _announcedata->getFloat(POSITION_MANTISSA);
		float z = _announcedata->getFloat(POSITION_MANTISSA);
		Player* player = new Player;
		player->Register_net_node(this, player_id);
		player->Set_position(Vector3(x, y, z));
		play->Add_player(player, _role==eZCom_RoleOwner);
	}
	if (_requested_class == heightmap_id) 
	{
		printf("Client: Heightmap requested\n");
		Heightmap* heightmap = new Heightmap;
		heightmap->Register_net_node(this, heightmap_id);
		play->Add_heightmap(heightmap);
	}
}
