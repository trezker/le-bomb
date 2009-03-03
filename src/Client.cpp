#include "Client.h"
#include <iostream>
#include "Bomb.h"

void Client::Register_classes()
{
	bomb_id = ZCom_registerClass("Bomb");
}

void Client::Send_data(ZCom_BitStream *message)
{
	ZCom_sendData(server_id, message);
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
	printf("Connection to server closed. Exiting...\n");
//	exit_now = true;
}

void Client::ZCom_cbZoidResult( ZCom_ConnID _id, eZCom_ZoidResult _result, zU8 _new_level, ZCom_BitStream & _reason )
{
	if (_result == eZCom_ZoidEnabled)
		printf("Zoidlevel %d entered\n", _new_level);
	else
		printf("Failed entering Zoidlevel %d\n", _new_level);
}

void Client::ZCom_cbNodeRequest_Dynamic( ZCom_ConnID _id, ZCom_ClassID _requested_class, ZCom_BitStream *_announcedata, eZCom_NodeRole _role, ZCom_NodeID _net_id ) 
{
	if (_requested_class == bomb_id) 
	{
		Bomb* bomb = new Bomb;
		bomb->Register_net_node(this, bomb_id);
	}
}
