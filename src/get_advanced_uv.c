#include "minirt.h"

void	get_torus_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	rel;
	double	u;
	double	v;
	double	theta;

	rel = vec3_sub(hit_point, obj->pt);
	theta = atan2(rel.z, rel.x);
	if (theta < 0)
		theta += 2.0 * M_PI;
	u = theta / (2.0 * M_PI);
	v = (vec3_dot(rel, obj->n) + obj->scal2) / (2.0 * obj->scal2);
	if (!obj->checkered)
	{
		map[0] = (int)floor(u * obj->texture_width);
		map[1] = (int)floor(v * obj->texture_height);
	}
	else
	{
		map[0] = (int)floor(u * 10);
		map[1] = (int)floor(v * 10);
	}
}

void	get_moebius_uv(t_obj *obj, t_vec3 p, int map[2])
{
	t_vec3	rel;
	double	w;
	double	u;
	double	v;

	w = obj->scal;
	rel = vec3_sub(p, obj->pt);
	u = atan2(rel.y, rel.x);
	if (u < 0)
		u += 2.0 * M_PI;
	v = rel.z / w;
	if (v > 1.0)
		v = 1.0;
	if (v < -1.0)
		v = -1.0;
	if (!obj->checkered)
	{
		map[0] = (int)floor(u / (2.0 * M_PI) * obj->texture_width);
		map[1] = (int)floor((v + 1.0) * 0.5 * obj->texture_height);
	}
	else
	{
		map[0] = (int)floor(u / (2.0 * M_PI) * 10);
		map[1] = (int)floor((v + 1.0) * 0.5 * 5);
	}
}
