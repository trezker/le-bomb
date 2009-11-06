#ifndef Editor_h
#define Editor_h

#include <scenegraph/Scenenode.h>
#include <Heightmap.h>
#include <scenegraph/Cameranode.h>
#include <scenegraph/Lightnode.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_opengl.h>
#include "Gamestate.h"

class Editor: public Gamestate
{
public:
	Editor();
	~Editor();
	void Init();
	void Set_heightmap(Heightmap* h);
	void Update(double dt);
	void Render();
	void Event(ALLEGRO_EVENT event);
private:
	Scenenode root;
	Cameranode* camera;
	Lightnode* light;
	Heightmap* heightmap;

	bool move_forward;
	bool move_backward;
	bool move_left;
	bool move_right;
	bool move_up;
	bool move_down;

	float fov;
	float near;
	float far;
	int width;
	int height;
};

#endif
