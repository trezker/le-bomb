#ifndef Player_h
#define Player_h

#include "Transformnode.h"
#include "Modelnode.h"
#include "Scenenode.h"
#include <allegro5/allegro5.h>

class Player: public Scenenode
{
public:
	Player();
	~Player();
	void Set_position(Vector3 p);
	Vector3 Get_position();
	void Set_texture(ALLEGRO_BITMAP* t);
//	void Update(double dt, Vector3 cam);

/*	bool Deleteme();
	void Register_net_node(ZCom_Control *_control, ZCom_ClassID class_id);
	void Process_net_events();
*/
private:
	Transformnode* transform;
	Modelnode* model;
};

#endif
