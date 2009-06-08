#include "scenegraph/Animated_modelnode.h"
#include <fstream>
#include "math/Vector3.h"
#include "scenegraph/Quadnode.h"

Animated_modelnode::Animated_modelnode()
{
	paused = false;
	animated = 0;
	skeleton = NULL;
}

Animated_modelnode::~Animated_modelnode()
{
	FreeModel (&md5file);
	
//	FreeAnim (&md5anim);

	if (animated && skeleton)
	{
		Destroy_skeleton(skeleton);
		skeleton = NULL;
	}
}

void Animated_modelnode::Set_texture(ALLEGRO_BITMAP* t)
{
	texture = t;
}

void Animated_modelnode::Load_model(const std::string& filename)
{
	/* Load MD5 model file */
	if (!ReadMD5Model (filename.c_str(), &md5file))
	{
		//Todo: Handle error
		return;
	}
	skeleton = Create_skeleton(md5file.num_joints);
}

void Animated_modelnode::Load_animation(const std::string& filename, const std::string &name)
{
	/* Load MD5 animation file */
	active_animation = &animations[name];
	if (!ReadMD5Anim (filename.c_str(), active_animation))
	{
		FreeAnim (active_animation);
	}
	else
	{
		animInfo.curr_frame = 0;
		animInfo.next_frame = 1;

		animInfo.last_time = 0;
		animInfo.max_time = 1.0 / active_animation->frameRate;

		/* Allocate memory for animated skeleton */
//		skeleton = Create_skeleton(active_animation->num_joints);
		animated = 1;
	}
}

void Animated_modelnode::Prerender()
{
	if(texture)
	{
		glBindTexture(GL_TEXTURE_2D, al_get_opengl_texture(texture));
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);

		glAlphaFunc(GL_GREATER,0.1f);
		glEnable(GL_ALPHA_TEST);
	}
}

void Animated_modelnode::Render()
{
	/* Draw skeleton */
//	DrawSkeleton (skeleton, md5file.num_joints);

	Draw_model(md5file, skeleton);
}

void Animated_modelnode::Postrender()
{
	if(texture)
	{
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_TEXTURE_2D);
		glShadeModel(GL_FLAT);
		glDisable(GL_ALPHA_TEST);
	}
}

void Animated_modelnode::Update(double dt)
{
	if (animated && active_animation)
	{
		/* Calculate current and next frames */
		if(!paused)
		{
			Animate (active_animation, &animInfo, dt);
		}

		/* Interpolate skeletons between two frames */
		InterpolateSkeletons (active_animation->skelFrames[animInfo.curr_frame],
			active_animation->skelFrames[animInfo.next_frame],
			active_animation->num_joints,
			animInfo.last_time * active_animation->frameRate,
			skeleton);
	}
	else
	{
		/* No animation, use bind-pose skeleton */
		skeleton = md5file.baseSkel;
	}
}

void Animated_modelnode::Pause_animation(bool b)
{
	paused = b;
}

void Animated_modelnode::Play_animation(const std::string& name, bool loop)
{
	if(animations.find(name) != animations.end())
	{
		active_animation = &animations[name];
		animInfo.curr_frame = 0;
		animInfo.next_frame = 1;

		animInfo.last_time = 0;
		animInfo.max_time = 1.0 / active_animation->frameRate;
		animInfo.loop = loop;
	}
	else
	{
		active_animation = NULL;
	}
}

bool Animated_modelnode::Animation_has_ended()
{
	if(active_animation)
	{
		if(animInfo.next_frame == 0)
			return true;
	}
	return false;
}
