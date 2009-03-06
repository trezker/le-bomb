#ifndef Cameranode_h
#define Cameranode_h

#include <vector>
#include "Vector3.h"
#include "Scenenode.h"

class Cameranode: public Scenenode
{
public:
	Cameranode();

	void Look_at(Vector3 p);
	Vector3 Get_up();
	Vector3 Get_front();
	Vector3 Get_right();

	void Set_position(Vector3 v);
	void Set_rotation(Vector3 v);
	Vector3 Get_position();
	Vector3 Get_rotation();
	
	virtual void Prerender();
	virtual void Postrender();
private:
	Vector3 position;
	Vector3 rotation;
	bool lookat;
	Vector3 lookat_target;
	Vector3 up;
	Vector3 front;
	Vector3 right;
	float matrix[16];
};

#endif