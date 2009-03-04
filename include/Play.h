#ifndef Play_h
#define Play_h

#include <Scenenode.h>
#include <Heightmap.h>
#include <Cameranode.h>
#include <Lightnode.h>
#include <allegro5/allegro5.h>
#include <allegro5/a5_iio.h>
#include <allegro5/a5_font.h>
#include <allegro5/a5_ttf.h>
#include <allegro5/a5_opengl.h>
#include "Billboardnode.h"
#include "Gamestate.h"
#include "Modelnode.h"
#include "Transformnode.h"
#include <vector>
#include "Bomb.h"
#include "Server.h"
#include "Client.h"
#include "Player.h"

class Play: public Gamestate
{
public:
	Play();
	~Play();
	void Init();
	void Set_heightmap(Heightmap* h);
	void Update(double dt);
	void Render();
	void Event(ALLEGRO_EVENT event);
	
	void Add_bomb(Bomb* bomb);
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

	ALLEGRO_BITMAP* bomb_texture;
	Billboardnode* billboard;
	Player* player;
	typedef std::vector<Bomb*> Bombs;
	Bombs bombs;
	
	Server* server;
	Client *client;
	ALLEGRO_CONFIG* netconf;
};

#endif
