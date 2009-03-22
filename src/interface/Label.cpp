#include "interface/Label.h"
#include "interface/Renderer.h"

namespace interface
{

Label::Label()
:halignment(HALIGN_LEFT)
,valignment(VALIGN_TOP)
{
}

Widget* Label::Clone()
{
	return new Label(*this);
}

void Label::Render()
{
	Renderer* renderer = Get_renderer();
	renderer->Draw_text(Get_bounding_rect(), text, halignment, valignment, al_map_rgb(255, 255, 255));
}

void Label::Set_text(const std::string& t)
{
	text = t;
}

void Label::Set_alignment(HAlignment a)
{
	halignment = a;
}

void Label::Set_vertical_alignment(VAlignment a)
{
	valignment = a;
}

}
