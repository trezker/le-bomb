#ifndef Server_h
#define Server_h

#include <zoidcom/zoidcom.h>
#include "Bomb.h"
#include "Player.h"
#include "Heightmap.h"
#include <map>

class Server : public ZCom_Control {
public:
	Server();
	~Server();
	void Init();
	void Register_classes();
	void Update(double dt);
private:
	ZCom_ClassID bomb_id;
	ZCom_ClassID player_id;
	ZCom_ClassID heightmap_id;
	
	Heightmap* heightmap;
	typedef std::vector<Bomb*> Bombs;
	Bombs bombs;
	typedef std::map<ZCom_ConnID, Player*> Players;
	Players players;

	void ZCom_cbConnectResult( ZCom_ConnID _id, eZCom_ConnectResult _result, ZCom_BitStream &_reply ) {}
	bool ZCom_cbConnectionRequest( ZCom_ConnID  _id, ZCom_BitStream &_request, ZCom_BitStream &_reply );
	void ZCom_cbConnectionSpawned( ZCom_ConnID _id );
	void ZCom_cbConnectionClosed( ZCom_ConnID _id, eZCom_CloseReason _reason, ZCom_BitStream &_reasondata );
	bool ZCom_cbZoidRequest( ZCom_ConnID _id, zU8 _requested_level, ZCom_BitStream &_reason );
	void ZCom_cbZoidResult( ZCom_ConnID _id, eZCom_ZoidResult _result, zU8 _new_level, ZCom_BitStream &_reason ) {}
	void ZCom_cbNodeRequest_Dynamic( ZCom_ConnID _id, ZCom_ClassID _requested_class, ZCom_BitStream *_announcedata,
								   eZCom_NodeRole _role, ZCom_NodeID _net_id ) {}
	void ZCom_cbNodeRequest_Tag( ZCom_ConnID _id, ZCom_ClassID _requested_class, ZCom_BitStream *_announcedata, 
							   eZCom_NodeRole _role, zU32 _tag ) {}
	void ZCom_cbDataReceived( ZCom_ConnID _id, ZCom_BitStream &_data );
	bool ZCom_cbDiscoverRequest( const ZCom_Address &_addr, 
							   ZCom_BitStream &_request, ZCom_BitStream &_reply ) {return false;}
	void ZCom_cbDiscovered( const ZCom_Address & _addr, ZCom_BitStream &_reply )  {}
};

#endif
