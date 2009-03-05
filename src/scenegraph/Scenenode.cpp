#include "scenegraph/Scenenode.h"
#include <allegro5/allegro5.h>
#include <allegro5/a5_iio.h>
#include <allegro5/a5_font.h>
#include <allegro5/a5_ttf.h>
#include <allegro5/a5_opengl.h>
#include <algorithm>

void Scenenode::Attach_node(Scenenode* node)
{
	children.push_back(node);
}

void Scenenode::Detach_node(Scenenode* node)
{
	children.erase(std::find(children.begin(), children.end(), node));
}

void Scenenode::Apply()
{
	Prerender();
	Render();
	for(Children::iterator i = children.begin(); i!=children.end(); ++i)
	{
		(*i)->Apply();
	}
	Postrender();
}
