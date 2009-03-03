#include "Server.h"
#include <iostream>

bool Server::ZCom_cbConnectionRequest(ZCom_ConnID  _id, ZCom_BitStream &_request, ZCom_BitStream &_reply )
{
	printf("A client requested connection - the new id is [%d].\n", _id);
	return true;
}

// someone has connected
void ZCom_cbConnectionSpawned( ZCom_ConnID _id )
{
	printf("New connection with id [%d]", _id);
}

// someone has disconnected
void ZCom_cbConnectionClosed( ZCom_ConnID _id, eZCom_CloseReason _reason, ZCom_BitStream &_reasondata )
{
	printf("Connection with id [%d] closed", _id);
}
