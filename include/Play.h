#ifndef Play_h
#define Play_h

#include "Heightmap.h"
#include "scenegraph/Scenenode.h"
#include "scenegraph/Cameranode.h"
#include "scenegraph/Lightnode.h"
#include "scenegraph/Billboardnode.h"
#include "scenegraph/Modelnode.h"
#include "scenegraph/Transformnode.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_opengl.h>
#include "Gamestate.h"
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
	void Update(double dt);
	void Render();
	void Event(ALLEGRO_EVENT event);
	
	void Add_heightmap(Heightmap* h);
	void Add_bomb(Bomb* bomb);
	void Add_player(Player* player, bool owner = false);
private:
	Scenenode root;
	Cameranode* camera;
	Lightnode* light;
	Heightmap* heightmap;

	float fov;
	float near;
	float far;
	int width;
	int height;
	
	float camera_distance;
	float camera_elevation;

	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* heightmap_texture;
	ALLEGRO_BITMAP* bomb_texture;
	ALLEGRO_BITMAP* darwinian_texture;
//	Billboardnode* billboard;
	Player* player;
	typedef std::vector<Bomb*> Bombs;
	Bombs bombs;
	typedef std::vector<Player*> Players;
	Players players;
	
	Server* server;
	Client *client;
	ALLEGRO_CONFIG* netconf;
};

#endif
