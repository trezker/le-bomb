#ifndef Heightmap_h
#define Heightmap_h

#include <vector>
#include "Scenenode.h"
#include "Vector3.h"
#include <allegro5/allegro5.h>
#include <allegro5/a5_iio.h>

struct Height_point
{
	float x;
	float y;
	float height;
};
typedef std::vector<Height_point> Height_points;

struct Height_point_data
{
	Height_point_data()
	:height(0), normal_dirty(false){}
	float height;
	Vector3 normal;
	bool normal_dirty;
};

class Heightmap: public Scenenode
{
public:
	Heightmap();
	float Get_width_x();
	float Get_width_z();
	/* Function: Set_height
	 * Sets the height of the point nearest given coordinates.
	 * */
	void Set_height(float x, float y, float height);
	/* Function: Get_height
	 * Gets the height of the point nearest given coordinates.
	 * */
	float Get_height(float x, float y);
	Height_points Get_height_points_in_circle(float x, float y, float radius);
	
	void Recalc_normals();
	
	virtual void Render();
private:
	Vector3 Calc_normals_helper(Vector3 p, int x2, int y2, int x3, int y3);
	void Calc_normals_around(int x, int y);

	typedef std::vector<Height_point_data> Row;
	typedef std::vector<Row> Rows;
	Rows rows;
	float tilesize;
	ALLEGRO_BITMAP* texture;
};

#endif
