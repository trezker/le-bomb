#ifndef Animated_modelnode_h
#define Animated_modelnode_h

#include "Scenenode.h"
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/a5_opengl.h>
#include <vector>
#include "math/Vector3.h"
#include "md5/md5model.h"

class Animated_modelnode: public Scenenode
{
public:
	Animated_modelnode();
	~Animated_modelnode();
	void Set_texture(ALLEGRO_BITMAP* t);
	void Load_model(const std::string& filename);
	void Load_animation(const std::string& filename);
	virtual void Prerender();
	virtual void Render();
	virtual void Postrender();
	
	void Update(double dt);
private:
	ALLEGRO_BITMAP* texture;

	struct md5_model_t md5file;
	struct md5_anim_t md5anim;

	int animated;

	struct md5_joint_t *skeleton;
	struct anim_info_t animInfo;

	vec3_t *vertexArray;
	GLuint *vertexIndices;

	int max_verts;
	int max_tris;
};

#endif
