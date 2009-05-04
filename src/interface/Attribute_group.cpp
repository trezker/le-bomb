#include "interface/Attribute_group.h"

namespace interface
{

Attribute_group::Attribute_group()
:height(0)
{
}

float Attribute_group::Get_height()
{
	return height;
}

void Attribute_group::Set_height(float h)
{
	height = h;
}

void Attribute_group::Event(ALLEGRO_EVENT event)
{
}

}
