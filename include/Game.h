#ifndef Game_h
#define Game_h

#include <allegro5/allegro5.h>
#include <allegro5/a5_iio.h>
#include <allegro5/a5_font.h>
#include <allegro5/a5_ttf.h>
#include <allegro5/a5_opengl.h>
#include "Gamestate.h"

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
	void Init();

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
};


#endif  //  Game_h
