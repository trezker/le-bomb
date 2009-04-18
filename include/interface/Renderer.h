#ifndef interface_Renderer_h
#define interface_Renderer_h

#include <map>
#include <list>
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/a5_font.h>
#include "interface/Widget.h"
#include "interface/Rect.h"

namespace interface
{

class Renderable
{};

enum Direction{
	TRIANGLE_UP,
	TRIANGLE_DOWN,
};

class Renderer
{
public:
	Renderer();
	void Set_font(ALLEGRO_FONT* f);
	ALLEGRO_FONT* Get_font();
	
	void Render();
	void Add_widget(Widget* w);
	void Remove_widget(Widget* w);
	
	void Draw_rect(Rect rect, ALLEGRO_COLOR c);
	void Draw_triangle(Rect rect, Direction d);
	void Draw_raised_panel(Rect rect);
	void Draw_sunken_panel(Rect rect);
	void Draw_text_field(Rect rect);
	void Draw_text(Rect rect, const std::string& text, HAlignment halignment, VAlignment valignment, ALLEGRO_COLOR color);
private:
	bool use_cache;

	typedef std::list<Renderable> Renderables;
	typedef std::map<Widget*, Renderables> Widget_cache;
	Widget_cache widget_cache;

	//Rendering order
	typedef std::list<Widget*> Widgets;
	Widgets widgets;
	
	ALLEGRO_FONT* font;
};

void Set_renderer(Renderer* renderer);
Renderer* Get_renderer();

}

#endif
