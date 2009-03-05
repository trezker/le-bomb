#ifndef Functions_h
#define Functions_h

#include "Vector3.h"
#include "scenegraph/Cameranode.h"

void Prerender_perspective_view(float fov, float aspect, float near, float far);
void Postrender_perspective_view();

Vector3 GetOGLPos(int x, int y, Cameranode* camera);
Vector3 Get_OGL_normal(Vector3 oglpoint, Vector3 camera_position);

#endif
