#include "Lightnode.h"
#include <allegro5/allegro5.h>
#include <allegro5/a5_opengl.h>

void Lightnode::Prerender()
{
	float ms = al_current_time();
	GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]= { -1.0f, 1.0f, -1.0f, 0.0f };
//		GLfloat LightPosition[]= { cos(ms)*50+50, 10.0f, sin(ms)*50+50, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);
}

void Lightnode::Postrender()
{
	glDisable(GL_LIGHT1);
}
