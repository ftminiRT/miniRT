#include "minirt.h"

t_basis	make_basis(t_vec3 n)
{
	t_basis	b;
	t_vec3	tmp;

	b.w = vec3_normalized(n);
	if (fabs(b.w.x) < 1e-6 && fabs(b.w.z) < 1e-6)
		tmp = (t_vec3){1, 0, 0};
	else
		tmp = (t_vec3){0, 1, 0};
	b.u = vec3_normalized(vec3_cross(tmp, b.w));
	b.v = vec3_cross(b.w, b.u);
	return (b);
}

t_vec3	world_to_local_point(t_vec3 p, t_obj *obj, t_basis b)
{
	t_vec3	rel;

	rel = vec3_sub(p, obj->pt);
	return (world_to_local_vec(rel, b));
}

t_vec3	world_to_local_vec(t_vec3 v, t_basis b)
{
	return ((t_vec3){vec3_dot(v, b.u), vec3_dot(v, b.v), vec3_dot(v, b.w)});
}

t_vec3	local_to_world_vec(t_vec3 v, t_basis b)
{
	return ((t_vec3){b.u.x * v.x + b.v.x * v.y + b.w.x * v.z, b.u.y * v.x
		+ b.v.y * v.y + b.w.y * v.z, b.u.z * v.x + b.v.z * v.y + b.w.z * v.z});
}

t_ray	world_to_local_ray(t_ray r, t_obj *obj, t_basis b)
{
	t_ray	out;

	out.pt = world_to_local_vec(vec3_sub(r.pt, obj->pt), b);
	out.dir = world_to_local_vec(r.dir, b);
	return (out);
}
