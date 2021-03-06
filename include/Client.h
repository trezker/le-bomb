#ifndef Client_h
#define Client_h

#include <zoidcom/zoidcom.h>
class Play;

class Client : public ZCom_Control {
public:
	Client();
	~Client();
	void Update(double dt);
	void Set_play(Play* play);
	void Register_classes();
	void Send_data(ZCom_BitStream *message);
	bool Ready();
	bool Disconnected();
private:
	bool ready;
	bool disconnected;
	Play* play;
	ZCom_ConnID server_id;
	ZCom_ClassID heightmap_id;
	ZCom_ClassID bomb_id;
	ZCom_ClassID player_id;

	void ZCom_cbConnectResult( ZCom_ConnID _id, eZCom_ConnectResult _result, ZCom_BitStream &_reply );
	bool ZCom_cbConnectionRequest( ZCom_ConnID  _id, ZCom_BitStream &_request, ZCom_BitStream &_reply ){return false;}
	void ZCom_cbConnectionSpawned( ZCom_ConnID _id ) {}
	void ZCom_cbConnectionClosed( ZCom_ConnID _id,  eZCom_CloseReason _reason, ZCom_BitStream &_reasondata );
	bool ZCom_cbZoidRequest( ZCom_ConnID _id, zU8 _requested_level, ZCom_BitStream &_reason ) {return false;}
	void ZCom_cbZoidResult( ZCom_ConnID _id, eZCom_ZoidResult _result, zU8 _new_level, ZCom_BitStream &_reason );
	void ZCom_cbNodeRequest_Dynamic( ZCom_ConnID _id, ZCom_ClassID _requested_class, ZCom_BitStream *_announcedata,
								   eZCom_NodeRole _role, ZCom_NodeID _net_id );
	void ZCom_cbNodeRequest_Tag( ZCom_ConnID _id, ZCom_ClassID _requested_class, ZCom_BitStream *_announcedata,
							   eZCom_NodeRole _role, zU32 _tag ) {}
	void ZCom_cbDataReceived( ZCom_ConnID _id, ZCom_BitStream &_data ) {}
	bool ZCom_cbDiscoverRequest( const ZCom_Address &_addr, 
							   ZCom_BitStream &_request, ZCom_BitStream &_reply ) {return false;}
	void ZCom_cbDiscovered( const ZCom_Address & _addr, ZCom_BitStream &_reply )  {}
};

#endif
