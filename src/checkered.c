#include "minirt.h"

int	ft_clamp(double x, int min, int max)
{
	if (x > max)
		x = max;
	if (x < min)
		x = min;
	return (x);
}

static void	get_plane_uv(t_obj *obj, t_vec3 hit_point, int map[2])
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
	map[0] = (int)floor(u);
	map[1] = (int)floor(v);
}

static void	get_sphere_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	d;
	double	u;
	double	v;

	(void)obj;
	d = vec3_normalized(vec3_sub(hit_point, obj->pt));
	u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
	v = 0.5 - asin(d.y) / M_PI;
	map[0] = (int)floor(u * 10);
	map[1] = (int)floor(v * 10);
}

t_color	get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	int	map[2];
	int	checker;

	(void)rt;
	if (obj->type == OT_PLANE)
		get_plane_uv(obj, hit_point, map);
	else if (obj->type == OT_SPHERE)
		get_sphere_uv(obj, hit_point, map);
	else if (obj->type == OT_CYL)
		get_cylinder_uv(obj, hit_point, map);
	else
		return (obj->color);
	checker = (map[0] + map[1]) % 2;
	if (checker == 0)
		return (obj->color);
	return ((t_color){0, 0, 0});
}
