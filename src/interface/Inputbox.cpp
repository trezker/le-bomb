#include "interface/Inputbox.h"
#include "interface/Renderer.h"

namespace interface
{

Widget* Inputbox::Clone()
{
	return new Inputbox(*this);
}

void Inputbox::Event(const ALLEGRO_EVENT &event)
{
}

void Inputbox::Render()
{
	Renderer* renderer = Get_renderer();
	renderer->Draw_text_field(Get_bounding_rect());
	Rect text_rect = Get_bounding_rect();
	text_rect.Shrink(2, 2);
	renderer->Draw_text(text_rect, text, HALIGN_LEFT, VALIGN_TOP, al_map_rgb(0, 0, 0));
}

void Inputbox::Set_text(const std::string& t)
{
	text = t;
}

std::string Inputbox::Get_text()
{
	return text;
}

}
