#include "minirt.h"


void	get_plane_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	ref;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	rel;
	double	u;
	double	v;

	ref = fabs(obj->n.y) < 0.9 ? (t_vec3){0, 1, 0} : (t_vec3){1, 0, 0};
	tangent = vec3_normalized(vec3_cross(ref, obj->n));
	bitangent = vec3_cross(obj->n, tangent);
	rel = vec3_sub(hit_point, obj->pt);
	u = vec3_dot(rel, tangent) / 100.0;
	v = vec3_dot(rel, bitangent) / 100.0;
	if (obj->checkered)
	{
		map[0] = (int)floor(u);
		map[1] = (int)floor(v);
	}
	else
	{
		map[0] = (int)floor(u * obj->texture_width);
		map[1] = (int)floor(v * obj->texture_height);

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

static void	get_cyl_body_uv(t_obj *obj, t_vec3 hit_point, double h, int map[2])
{
	t_vec3	from_center;
	t_vec3	radial;
	t_vec3	u_vec;
	t_vec3	v_vec;
	double	u;
	double	v;

	from_center = vec3_sub(hit_point, obj->pt);
	radial = vec3_sub(from_center, vec3_scalmult(h, obj->n));
	if (fabs(obj->n.x) < 0.9)
		u_vec = vec3_cross(obj->n, (t_vec3){1, 0, 0});
	else
		u_vec = vec3_cross(obj->n, (t_vec3){0, 1, 0});
	vec3_normalize(&u_vec);
	v_vec = vec3_cross(obj->n, u_vec);
	u = atan2(vec3_dot(radial, v_vec), vec3_dot(radial, u_vec));
	if (u < 0)
		u += 2.0 * M_PI;
	u /= (2.0 * M_PI);
	v = (h + obj->scal2 / 2.0) / obj->scal2;
	if (obj->checkered)
	{
		map[0] = (int)floor(u * 10.0) % 10;
		map[1] = (int)floor(v * 10.0);
		if (map[0] < 0)
			map[0] += 10;
	}
	else
	{
		map[0] = (int)floor(u * obj->texture_width) % obj->texture_width;
		map[1] = (int)floor(v * obj->texture_height);
		if (map[0] < 0)
			map[0] += obj->texture_width;
	}
}

static void	get_cyl_cap_uv(t_obj *obj, t_vec3 hit_point, double h, int map[2])
{
	t_vec3	center;
	t_vec3	local;
	t_vec3	u_vec;
	t_vec3	v_vec;
	double	lx;
	double	lz;

	if (h < 0)
		center = vec3_add(obj->pt, vec3_scalmult(-obj->scal2 / 2.0, obj->n));
	else
		center = vec3_add(obj->pt, vec3_scalmult(obj->scal2 / 2.0, obj->n));
	local = vec3_sub(hit_point, center);
	if (fabs(obj->n.x) < 0.9)
		u_vec = vec3_cross(obj->n, (t_vec3){1, 0, 0});
	else
		u_vec = vec3_cross(obj->n, (t_vec3){0, 1, 0});
	vec3_normalize(&u_vec);
	v_vec = vec3_cross(obj->n, u_vec);
	lx = vec3_dot(local, u_vec) / obj->scal;
	lz = vec3_dot(local, v_vec) / obj->scal;
	if (obj->checkered)
	{
		map[0] = ((int)floor((lx + 1.0) * 5.0) % 10 + 10) % 10;
		map[1] = ((int)floor((lz + 1.0) * 5.0) % 10 + 10) % 10;
	}
	else
	{
    map[0] = ((int)floor((lx + 1) * 0.5* obj->texture_width) % obj->texture_width + obj->texture_width) % obj->texture_width;
    map[1] = ((int)floor((lz + 1) * 0.5 * obj->texture_height) % obj->texture_height + obj->texture_height) % obj->texture_height;
	}

}

void	get_cylinder_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	from_center;
	double	h;

	from_center = vec3_sub(hit_point, obj->pt);
	h = vec3_dot(from_center, obj->n);
	if (fabs(h) <= obj->scal2 / 2.0 - EPSILON)
		get_cyl_body_uv(obj, hit_point, h, map);
	else
		get_cyl_cap_uv(obj, hit_point, h, map);
}