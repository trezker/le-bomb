#include "Cameranode.h"
#include <allegro5/allegro5.h>
#include <allegro5/a5_iio.h>
#include <allegro5/a5_font.h>
#include <allegro5/a5_ttf.h>
#include <allegro5/a5_opengl.h>


void Cameranode::Set_position(Vector3 v)
{
	position = v;
}

void Cameranode::Set_rotation(Vector3 v)
{
	rotation = v;
}

Vector3 Cameranode::Get_position()
{
	return position;
}

Vector3 Cameranode::Get_rotation()
{
	return rotation;
}

void Cameranode::Prerender()
{
	glPushMatrix();
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glTranslatef(-position.x, -position.y, -position.z);
}

void Cameranode::Postrender()
{
	glPopMatrix();
}
