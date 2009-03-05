#ifndef Modelnode_h
#define Modelnode_h

#include "Scenenode.h"
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/a5_opengl.h>

class Modelnode: public Scenenode
{
public:
	void Set_texture(ALLEGRO_BITMAP* t);
	void Loadmodel(const std::string& filename);
	virtual void Prerender();
	virtual void Postrender();
private:
	ALLEGRO_BITMAP* texture;
};

#endif
