#ifndef Bomb_h
#define Bomb_h

#include <allegro5/allegro5.h>
#include "Scenenode.h"
#include "Billboardnode.h"
#include "Quadnode.h"

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
private:
	Billboardnode* billboard;
	Quadnode* quad;
	float timeout;
};

#endif
