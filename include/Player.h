#ifndef Player_h
#define Player_h

#include "scenegraph/Transformnode.h"
#include "scenegraph/Modelnode.h"
#include "scenegraph/Scenenode.h"
#include "Heightmap.h"
#include <allegro5/allegro5.h>
#include <zoidcom/zoidcom.h>

class Player: public Scenenode
{
public:
	Player();
	~Player();
	void Set_position(Vector3 p);
	Vector3 Get_position();
	void Set_texture(ALLEGRO_BITMAP* t);
	void Update(double dt, Vector3 camera_right, Vector3 camera_front, Heightmap* heightmap);
	void Event(ALLEGRO_EVENT event);
	void Damage(float d);

	bool Deleteme();
	ZCom_Node* Register_net_node(ZCom_Control *_control, ZCom_ClassID class_id);
	void Process_net_events();
private:
	Vector3 position;
	Vector3 interpos;

	Transformnode* transform;
	Modelnode* model;

	bool move_forward;
	bool move_backward;
	bool move_left;
	bool move_right;
	bool move_up;
	bool move_down;
	
	float health;

	ZCom_Node* net_node;
	bool deleteme;
};

#endif
