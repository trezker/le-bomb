#ifndef Game_h
#define Game_h

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_opengl.h>
#include "Gamestate.h"
#include <zoidcom/zoidcom.h>
#include "Play.h"
#include "Editor.h"

/* Class: Game
 * The hub of the whole system, handling, initialization, cleanup, main loop, events and services.
 */
class Game
{
public:

	/* Constructor: Game
	 */
	Game();

	/* Destructor: Game
	 */
	~Game();

	/* Function: Run
	 * Runs the whole game, doesn't return until game exits.
	 */
	void Run();

	ALLEGRO_FONT* Get_font();

	/* Section: Private
	 */
private: //Functions

	/* Function: Init
	 * Initialize game
	 */
	bool Init();

	/* Function: Update
	 * Updates everything
	 *
	 * Parameters:
	 * dt - Time passed since last update.
	 */
	void Update(double dt);

	/* Function: Render
	 * Renders everything
	 */
	void Render();

	void Event(ALLEGRO_EVENT event);

private: //Members
	bool quit;
	ALLEGRO_FONT* font;
	Gamestate* gamestate;
	ZoidCom *zcom;
	Editor* editor;
	Play* play;
};


#endif  //  Game_h
