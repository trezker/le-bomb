#ifndef Quadnode_h
#define Quadnode_h

#include "Vector3.h"
#include "Scenenode.h"
#include <allegro5/allegro5.h>
#include <allegro5/a5_opengl.h>

class Quadnode: public Scenenode
{
public:
	Quadnode();
	void Set_corners(Vector3 p[4]);
	void Set_texture(ALLEGRO_BITMAP* t);
	virtual void Render();
private:
	Vector3 v[4];
	ALLEGRO_BITMAP* texture;
};

#endif
