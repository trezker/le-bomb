#ifndef Bomb_h
#define Bomb_h

#include <allegro5/allegro5.h>
#include "scenegraph/Scenenode.h"
#include "scenegraph/Billboardnode.h"
#include "scenegraph/Quadnode.h"
#include <zoidcom/zoidcom.h>
#include "Player.h"

class Bomb: public Scenenode
{
public:
	Bomb();
	~Bomb();
	void Set_position(Vector3 p);
	Vector3 Get_position();
	void Set_timeout(float t);
	void Set_texture(ALLEGRO_BITMAP* t);
	void Update(double dt, Vector3 cam);
	bool Exploded();
	float Damage_at(Vector3 p);
	Player* Get_player();
	void Set_player(Player* p);

	bool Deleteme();
	void Register_net_node(ZCom_Control *_control, ZCom_ClassID class_id);
	void Process_net_events();
private:
	Billboardnode* billboard;
	Quadnode* quad;
	float timeout;
	Player* player;

	ZCom_Node* net_node;
	bool deleteme;
};

#endif
