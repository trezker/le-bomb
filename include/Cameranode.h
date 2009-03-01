#ifndef Cameranode_h
#define Cameranode_h

#include <vector>
#include "Vector3.h"
#include "Scenenode.h"

class Cameranode: public Scenenode
{
public:
	void Set_position(Vector3 v);
	void Set_rotation(Vector3 v);
	Vector3 Get_position();
	Vector3 Get_rotation();
	
	virtual void Prerender();
	virtual void Postrender();
private:
	Vector3 position;
	Vector3 rotation;
};

#endif
