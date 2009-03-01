#include "Quadnode.h"

void Quadnode::Set_corners(Vector3 p[4])
{
	for(int i=0; i<4; ++i)
		v[i] = p[i];
}

void Quadnode::Set_texture(ALLEGRO_BITMAP* t)
{
	texture = t;
}

void Quadnode::Render()
{
	if(texture)
	{
		glBindTexture(GL_TEXTURE_2D, al_get_opengl_texture(texture));
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);

		glAlphaFunc(GL_GREATER,0.1f);
		glEnable(GL_ALPHA_TEST);
	}
	
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0); glVertex3f(-.5, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(+.5, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(+.5, +1, 0);
	glTexCoord2f(0, 1); glVertex3f(-.5, +1, 0);
	glEnd();

	glDisable(GL_ALPHA_TEST);
}
