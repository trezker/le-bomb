#include "Functions.h"
#include <GL/glu.h>

void Prerender_perspective_view(float fov, float aspect, float near, float far)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(fov, aspect, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Postrender_perspective_view()
{
	//Return to Allegros 2D world
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Vector3 GetOGLPos(int x, int y, Cameranode* camera)
{
	camera->Prerender();

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	camera->Postrender();

	return Vector3(posX, posY, posZ);
}

Vector3 Get_OGL_normal(Vector3 oglpoint, Vector3 camera_position)
{
	Vector3 mouse_vector = oglpoint - camera_position;
	mouse_vector.Normalize();
	return mouse_vector;
}


/*
Vector3 Get_mouse_vector()
{
	Vector3 rotation = camera->Get_rotation();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-rotation.z, 0, 0, 1);
	glRotatef(-rotation.y, 0, 1, 0);
	glRotatef(-rotation.x, 1, 0, 0);

	GLfloat m[16];
	glGetFloatv (GL_MODELVIEW_MATRIX, m);
	
	ALLEGRO_MOUSE_STATE ret_state;
	al_get_mouse_state(&ret_state);

	float xangle = (ret_state.x*fov/width - fov/2)*PI/180.f;
	float yangle = (ret_state.y*fov/height - fov/2)*PI/180.f;
	float x = sin(xangle)*width/height;
	float y = -sin(yangle);
	float z = -cos(xangle)*cos(yangle);

	Vector3 mouse_vector(
		(x * m[0] + y * m[4] + z * m[8] + m[12]),
		(x * m[1] + y * m[5] + z * m[9] + m[13]),
		(x * m[2] + y * m[6] + z * m[10] + m[14]));

	return mouse_vector;
}
*/
