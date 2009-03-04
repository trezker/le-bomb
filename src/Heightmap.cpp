#include "Heightmap.h"
#include <allegro5/allegro5.h>
#include <allegro5/a5_font.h>
#include <allegro5/a5_ttf.h>
#include <allegro5/a5_opengl.h>
#include <cmath>
#include <iostream>

Heightmap::Heightmap()
:tilesize(1)
{
	rows.resize(50);
	for(Rows::iterator i = rows.begin(); i!=rows.end(); ++i)
	{
		i->resize(50);
	}
	for(unsigned int ix = 0; ix<rows.size()-1; ++ix)
	{
		for(unsigned int iz = 0; iz<rows[0].size()-1; ++iz)
		{
			rows[ix][iz].normal = Vector3(0, 1, 0);
		}
	}
	texture = al_iio_load("media/floortilebig1b.jpg");
}

float Heightmap::Get_width_x()
{
	return rows.size()*tilesize;
}

float Heightmap::Get_width_z()
{
	return rows[0].size()*tilesize;
}

void Heightmap::Set_height(float ix, float iy, float height)
{
	int x = ix/tilesize+.5*tilesize;
	int y = iy/tilesize+.5*tilesize;
	if(x<0 || y<0 || x>=static_cast<int>(rows.size()) || y>=static_cast<int>(rows[0].size()))
		return;
	rows[x][y].height = height;
	rows[x][y].normal_dirty = true;
//	Calc_normals_around(x, y);
}

float Heightmap::Get_height(float ix, float iy)
{
/*	int x = ix/tilesize+.5*tilesize;
	int y = iy/tilesize+.5*tilesize;
	if(x<0 || y<0 || x>=static_cast<int>(rows.size()) || y>=static_cast<int>(rows[0].size()))
		return 0;
	return rows[x][y].height;
*/

	int tx = ix/tilesize;
	int tz = iy/tilesize;
	if(tx<0 || tz<0 || tx+1>=static_cast<int>(rows.size()) || tz+1>=static_cast<int>(rows[0].size()))
		return 0;

	float xp = (ix-tx)/tilesize;
	float zp = (iy-tz)/tilesize;
	float hx1 = (rows[tx+1][tz].height-rows[tx][tz].height)*xp+rows[tx][tz].height;
	float hx2 = (rows[tx+1][tz+1].height-rows[tx][tz+1].height)*xp+rows[tx][tz+1].height;
	return (hx2-hx1)*zp+hx1;
}

Height_points Heightmap::Get_height_points_in_circle(float ix, float iy, float iradius) const
{
	int radius = iradius/tilesize+1;
	int cx = ix/tilesize+.5*tilesize;
	int cy = iy/tilesize+.5*tilesize;
	int sx = (cx-radius)<0?0:cx-radius;
	int sy = (cy-radius)<0?0:cy-radius;
	int ex = (cx+radius)>=static_cast<int>(rows.size())?static_cast<int>(rows.size()):cx+radius+1;
	int ey = (cy+radius)>=static_cast<int>(rows[0].size())?static_cast<int>(rows[0].size()):cy+radius+1;
	float radius_squared = iradius*iradius;

	Height_points height_points;
	for(int x = sx; x<ex; ++x)
	{
		for(int y = sy; y<ey; ++y)
		{
			float rx = x*tilesize;
			float ry = y*tilesize;
			float dx = rx-ix;
			float dy = ry-iy;
			if(dx*dx + dy*dy <= radius_squared)
			{
				Height_point height_point;
				height_point.x = rx;
				height_point.y = ry;
				height_point.height = rows[x][y].height;
				height_points.push_back(height_point);
			}
		}
	}
	return height_points;
}

void Heightmap::Apply_brush(float x, float z, float brush_size, float brush_pressure, const float *brush, int brush_points)
{
	float brush_scale = brush_points/brush_size;
	Height_points height_points = Get_height_points_in_circle(x, z, brush_size);
	for(Height_points::iterator height_point=height_points.begin(); height_point!=height_points.end(); ++height_point)
	{
		float dx = height_point->x-x;
		float dy = height_point->y-z;
		float r = sqrt(dx*dx + dy*dy)*brush_scale;
		int low = r;
		float p = r-low;
		if(low+1<brush_points )
		{
			float h = height_point->height+brush_pressure*((brush[low+1]-brush[low])*p+brush[low]);
			Set_height(height_point->x, height_point->y, h);
		}
	}
	Recalc_normals();
}

void Heightmap::Recalc_normals()
{
	for(unsigned int ix = 0; ix<rows.size()-1; ++ix)
	{
		for(unsigned int iz = 0; iz<rows[0].size()-1; ++iz)
		{
			if(rows[ix][iz].normal_dirty)
			{
				Calc_normals_around(ix, iz);
			}
		}
	}
}


Vector3 Heightmap::Calc_normals_helper(Vector3 p, int x2, int y2, int x3, int y3)
{
	if(x2<0 || y2<0 || x2>=static_cast<int>(rows.size()) || y2>=static_cast<int>(rows[0].size()))
		return Vector3();
	if(x3<0 || y3<0 || x3>=static_cast<int>(rows.size()) || y3>=static_cast<int>(rows[0].size()))
		return Vector3();
	Vector3 v1 = Vector3(x2, rows[x2][y2].height, y2) - p;
	Vector3 v2 = Vector3(x3, rows[x3][y3].height, y3) - p;
	return v2.CrossProduct( v1 );
}

//Calc the normal for given point
void Heightmap::Calc_normals_around(int x, int y)
{
	Vector3 sum;
	Vector3 p;
	p.x = x;
	p.y = rows[x][y].height;
	p.z = y;
	sum += Calc_normals_helper(p, x+1, y, x+1, y+1);
	sum += Calc_normals_helper(p, x+1, y+1, x, y+1);
	sum += Calc_normals_helper(p, x, y+1, x-1, y+1);
	sum += Calc_normals_helper(p, x-1, y+1, x-1, y);
	sum += Calc_normals_helper(p, x-1, y, x-1, y-1);
	sum += Calc_normals_helper(p, x-1, y-1, x, y-1);
	sum += Calc_normals_helper(p, x, y-1, x+1, y-1);
	sum += Calc_normals_helper(p, x+1, y-1, x+1, y);
	sum.Normalize();
	rows[x][y].normal = sum;
	rows[x][y].normal_dirty = false;
}

void Heightmap::Render()
{
 	glBindTexture(GL_TEXTURE_2D, al_get_opengl_texture(texture));
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_QUADS);
	float x = 0;
	for(unsigned int ix = 0; ix<rows.size()-1; ++ix)
	{
		float z = 0;
		for(unsigned int iz = 0; iz<rows[0].size()-1; ++iz)
		{
			Height_point_data hpd;

			hpd = rows[ix][iz];
			glNormal3f( hpd.normal.x, hpd.normal.y, hpd.normal.z);
			glTexCoord2f(0, 0); glVertex3f(x, hpd.height, z);

			hpd = rows[ix+1][iz];
			glNormal3f( hpd.normal.x, hpd.normal.y, hpd.normal.z);
			glTexCoord2f(1, 0); glVertex3f(x+tilesize, rows[ix+1][iz].height, z);
			
			hpd = rows[ix+1][iz+1];
			glNormal3f( hpd.normal.x, hpd.normal.y, hpd.normal.z);
			glTexCoord2f(1, 1); glVertex3f(x+tilesize, rows[ix+1][iz+1].height, z+tilesize);
			
			hpd = rows[ix][iz+1];
			glNormal3f( hpd.normal.x, hpd.normal.y, hpd.normal.z);
			glTexCoord2f(0, 1); glVertex3f(x, rows[ix][iz+1].height, z+tilesize);

			z+=tilesize;
		}
		x += tilesize;
	}
	glEnd();
	glDisable(GL_COLOR_MATERIAL);	
}
