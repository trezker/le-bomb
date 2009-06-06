#include "scenegraph/Animated_modelnode.h"
#include <fstream>
#include "math/Vector3.h"
#include "scenegraph/Quadnode.h"

Animated_modelnode::Animated_modelnode()
{
	animated = 0;

	skeleton = NULL;

	vertexArray = NULL;
	vertexIndices = NULL;

	max_verts = 0;
	max_tris = 0;
}

Animated_modelnode::~Animated_modelnode()
{
	FreeModel (&md5file);
	FreeAnim (&md5anim);

	if (animated && skeleton)
	{
		Destroy_skeleton(skeleton);
		skeleton = NULL;
	}

	FreeVertexArrays (&vertexArray, &vertexIndices);
}

void Animated_modelnode::Set_texture(ALLEGRO_BITMAP* t)
{
	texture = t;
}

void Animated_modelnode::Load_model(const std::string& filename)
{
	/* Load MD5 model file */
	if (!ReadMD5Model (filename.c_str(), &md5file, &max_verts, &max_tris))
	{
		//Todo: Handle error
		return;
	}

	AllocVertexArrays (&vertexArray, &vertexIndices, max_verts, max_tris);
}

void Animated_modelnode::Load_animation(const std::string& filename)
{
	/* Load MD5 animation file */
	if (!ReadMD5Anim (filename.c_str(), &md5anim))
	{
		FreeAnim (&md5anim);
	}
	else
	{
		animInfo.curr_frame = 0;
		animInfo.next_frame = 1;

		animInfo.last_time = 0;
		animInfo.max_time = 1.0 / md5anim.frameRate;

		/* Allocate memory for animated skeleton */
		skeleton = Create_skeleton(md5anim.num_joints);
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

	Draw_model(md5file, skeleton, vertexArray, vertexIndices); 
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
	if (animated)
	{
		/* Calculate current and next frames */
		Animate (&md5anim, &animInfo, dt);

		/* Interpolate skeletons between two frames */
		InterpolateSkeletons (md5anim.skelFrames[animInfo.curr_frame],
			md5anim.skelFrames[animInfo.next_frame],
			md5anim.num_joints,
			animInfo.last_time * md5anim.frameRate,
			skeleton);
	}
	else
	{
		/* No animation, use bind-pose skeleton */
		skeleton = md5file.baseSkel;
	}
}
