#ifndef Billboardnode_h
#define Billboardnode_h

#include "Vector3.h"
#include "Scenenode.h"

class Billboardnode: public Scenenode
{
public:
	void Set_position(Vector3 p);
	void Update_vectors(Vector3 camera_position);
	virtual void Prerender();
	virtual void Postrender();
private:
	Vector3 position;
	float matrix[16];
};

#endif
