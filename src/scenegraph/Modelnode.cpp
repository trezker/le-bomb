#include "scenegraph/Modelnode.h"
#include <fstream>
#include "Vector3.h"
#include "scenegraph/Quadnode.h"

void Modelnode::Set_texture(ALLEGRO_BITMAP* t)
{
	texture = t;
}

void Modelnode::Loadmodel(const std::string& filename)
{
	std::ifstream f;
	f.open(filename.c_str());
	while(!f.eof())
	{
		Vector3 p[4];
		for(int i=0; i<4; ++i)
		{
			f>>p[i].x;
			f>>p[i].z;
			f>>p[i].y;
		}
		Quadnode* quad = new Quadnode;
		quad->Set_corners(p);
		Attach_node(quad);
	}
}

void Modelnode::Prerender()
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

void Modelnode::Postrender()
{
	if(texture)
	{
		glDisable(GL_ALPHA_TEST);
	}
}
