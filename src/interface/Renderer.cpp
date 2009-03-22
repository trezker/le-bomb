#include "interface/Renderer.h"
#include <algorithm>
#include <allegro5/a5_primitives.h>

namespace interface
{

Renderer* renderer = NULL;

void Set_renderer(Renderer* r)
{
	renderer = r;
}

Renderer* Get_renderer()
{
	return renderer;
}

Renderer::Renderer()
:use_cache(false)
,font(NULL)
{
}

void Renderer::Set_font(ALLEGRO_FONT* f)
{
	font = f;
}

void Renderer::Render()
{
	for(Widgets::iterator i = widgets.begin(); i != widgets.end(); ++i)
	{
		if(!use_cache)
		{
			(*i)->Render();
		}
		else if((*i)->Is_dirty())
		{
			widget_cache[*i].clear(); 
			(*i)->Render();
			(*i)->Set_dirty(false);
		}
	}
}

void Renderer::Add_widget(Widget* w)
{
	widgets.push_back(w);
}

void Renderer::Remove_widget(Widget* w)
{
	Widgets::iterator i = std::find(widgets.begin(), widgets.end(), w);
	if(i != widgets.end())
	{
		widgets.erase(i);
	}
}

void Renderer::Draw_rect(Rect rect, ALLEGRO_COLOR c)
{
	al_draw_rectangle(rect.Topleft().x, rect.Topleft().y, rect.Bottomright().x, rect.Bottomright().y
					, c, 0);
}

void Renderer::Draw_raised_panel(Rect rect)
{
	al_draw_rectangle(rect.Topleft().x, rect.Topleft().y, rect.Bottomright().x, rect.Bottomright().y
					, al_map_rgba(200, 200, 200, 255), 0);
	al_draw_rectangle(rect.Topleft().x+1, rect.Topleft().y+1, rect.Bottomright().x-1, rect.Bottomright().y-1
					, al_map_rgba(100, 100, 100, 255), 0);
	al_draw_filled_rectangle(rect.Topleft().x+2, rect.Topleft().y+2, rect.Bottomright().x-2, rect.Bottomright().y-2
					, al_map_rgba(200, 200, 200, 255));
}

void Renderer::Draw_sunken_panel(Rect rect)
{
	al_draw_rectangle(rect.Topleft().x, rect.Topleft().y, rect.Bottomright().x, rect.Bottomright().y
					, al_map_rgba(200, 200, 200, 255), 0);
	al_draw_rectangle(rect.Topleft().x+1, rect.Topleft().y+1, rect.Bottomright().x-1, rect.Bottomright().y-1
					, al_map_rgba(100, 100, 100, 255), 0);
	al_draw_filled_rectangle(rect.Topleft().x+2, rect.Topleft().y+2, rect.Bottomright().x-2, rect.Bottomright().y-2
					, al_map_rgba(100, 100, 100, 255));
}

void Renderer::Draw_text_field(Rect rect)
{
	al_draw_rectangle(rect.Topleft().x, rect.Topleft().y, rect.Bottomright().x, rect.Bottomright().y
					, al_map_rgba(200, 200, 200, 255), 0);
	al_draw_rectangle(rect.Topleft().x+1, rect.Topleft().y+1, rect.Bottomright().x-1, rect.Bottomright().y-1
					, al_map_rgba(100, 100, 100, 255), 0);
	al_draw_filled_rectangle(rect.Topleft().x+2, rect.Topleft().y+2, rect.Bottomright().x-2, rect.Bottomright().y-2
					, al_map_rgba(250, 250, 250, 255));
}

void Renderer::Draw_text(Rect rect, const std::string& text, HAlignment halignment, VAlignment valignment, ALLEGRO_COLOR color)
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, color);

	float y = rect.Topleft().y;
	if(valignment == VALIGN_BOTTOM)
		y = rect.Bottomright().y - al_font_text_height(font);
	if(valignment == VALIGN_CENTER)
		y = (y + rect.Bottomright().y - al_font_text_height(font))/2;
	if(halignment == HALIGN_LEFT)
		al_font_textout(font, rect.Topleft().x, y, text.c_str(), -1);
	if(halignment == HALIGN_RIGHT)
		al_font_textout_right(font, rect.Bottomright().x, y, text.c_str(), -1);
	if(halignment == HALIGN_CENTER)
		al_font_textout_centre(font, (rect.Topleft().x+rect.Bottomright().x)/2, y, text.c_str(), -1);
	
	al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(1, 1, 1, 1));
}

}
