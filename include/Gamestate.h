#ifndef Gamestate_h
#define Gamestate_h

#include <allegro5/allegro5.h>

class Gamestate
{
public:
	~Gamestate();
	virtual void Init()=0;
	virtual void Update(double dt)=0;
	virtual void Render()=0;
	virtual void Event(ALLEGRO_EVENT event)=0;
};

#endif
