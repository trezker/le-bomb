#ifndef Animated_modelnode_h
#define Animated_modelnode_h

#include "Scenenode.h"
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/a5_opengl.h>
#include <vector>
#include <map>
#include "math/Vector3.h"
#include "scenegraph/md5model.h"

class Animated_modelnode: public Scenenode
{
public:
	Animated_modelnode();
	~Animated_modelnode();
	void Set_texture(ALLEGRO_BITMAP* t);
	void Load_model(const std::string& filename);
	void Load_animation(const std::string& filename, const std::string& name);
	void Pause_animation(bool b);
	virtual void Prerender();
	virtual void Render();
	virtual void Postrender();
	
	void Update(double dt);
private:
	typedef std::map<std::string, md5_anim_t> Animations;
	Animations animations;
	md5_anim_t *active_animation;

	ALLEGRO_BITMAP* texture;

	md5_model_t md5file;

	int animated;
	bool paused;

	md5_joint_t *skeleton;
	anim_info_t animInfo;

	vec3_t *vertexArray;
	GLuint *vertexIndices;

	int max_verts;
	int max_tris;
};

#endif
