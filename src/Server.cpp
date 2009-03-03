#include "Server.h"
#include <iostream>

void Server::Register_classes()
{
	bomb_id = ZCom_registerClass("Bomb");
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
		return true;
	else
		return false;
}
