#include "minirt.h"

void	get_plane_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3		ref;
	t_normap	uvmap;
	t_vec3		rel;

	if (fabs(obj->n.y) < 0.9)
		ref = (t_vec3){0, 1, 0};
	else
		ref = (t_vec3){1, 0, 0};
	uvmap.tangent = vec3_normalized(vec3_cross(ref, obj->n));
	uvmap.bitangent = vec3_cross(obj->n, uvmap.tangent);
	rel = vec3_sub(hit_point, obj->pt);
	uvmap.u = vec3_dot(rel, uvmap.tangent) / 100.0;
	uvmap.v = vec3_dot(rel, uvmap.bitangent) / 100.0;
	if (obj->checkered)
	{
		map[0] = (int)floor(uvmap.u);
		map[1] = (int)floor(uvmap.v);
	}
	else
	{
		map[0] = (int)floor(uvmap.u * obj->texture_width);
		map[1] = (int)floor(uvmap.v * obj->texture_height);
	}
}

void	get_sphere_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	d;
	double	u;
	double	v;

	d = vec3_normalized(vec3_sub(hit_point, obj->pt));
	u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
	v = 0.5 - asin(d.y) / M_PI;
	if (obj->checkered)
	{
		map[0] = (int)floor(u * 10);
		map[1] = (int)floor(v * 10);
	}
	else
	{
		map[0] = (int)floor(u * obj->texture_width);
		map[1] = (int)floor(v * obj->texture_height);
	}
}
