#ifndef Heightmap_h
#define Heightmap_h

#include <vector>
#include "scenegraph/Scenenode.h"
#include "Vector3.h"
#include <allegro5/allegro5.h>
#include <allegro5/a5_iio.h>
#include <zoidcom/zoidcom.h>

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
	~Heightmap();
	float Get_width_x();
	float Get_width_z();
	/* Function: Set_height
	 * Sets the height of the point nearest given coordinates.
	 * */
	void Set_height(float x, float y, float height);
	/* Function: Get_height
	 * Gets the height of the point nearest given coordinates.
	 * */
	float Get_height(float x, float z);
	Vector3 Get_normal(float x, float z);
	Height_points Get_height_points_in_circle(float x, float y, float radius) const;
	
	void Apply_brush(float x, float z, float brush_size, float brush_pressure, const float *brush, int brush_points);
	
	void Recalc_normals();
	
	virtual void Render();

	bool Deleteme();
	void Register_net_node(ZCom_Control *_control, ZCom_ClassID class_id);
	void Process_net_events();
private:
	Vector3 Calc_normals_helper(Vector3 p, int x2, int y2, int x3, int y3);
	void Calc_normals_around(int x, int y);

	typedef std::vector<Height_point_data> Row;
	typedef std::vector<Row> Rows;
	Rows rows;
	float tilesize;
	ALLEGRO_BITMAP* texture;

	ZCom_Node* net_node;
	bool deleteme;
};

#endif
