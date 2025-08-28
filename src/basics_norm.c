#include "minirt.h"

t_vec3  sphere_norm(t_obj *obj, t_vec3 hit_point)
{
    t_vec3  normal;

    normal = vec3_sub(hit_point, obj->pt);
    vec3_normalize(&normal);
    return (normal);
}

t_vec3  plane_norm(t_obj *obj, t_vec3 hit_point)
{
    (void)hit_point;
    return (obj->n);
}

double     check_discs(t_obj *obj, t_vec3 hit_point)
{
	double	h;
	t_vec3	base_center;
	t_vec3	from_center;

    h = vec3_dot(vec3_sub(hit_point, obj->pt), obj->n);
    base_center = vec3_add(obj->pt, vec3_scalmult(-obj->scal2 / 2.0, obj->n));
    from_center = vec3_sub(hit_point, base_center);
    if (vec3_norm(from_center) <= obj->scal && h <= -obj->scal2 / 2.0 + EPSILON)
        return (1);
    base_center = vec3_add(obj->pt, vec3_scalmult(obj->scal2 / 2.0, obj->n));
    from_center = vec3_sub(hit_point, base_center);
    if (vec3_norm(from_center) <= obj->scal && h >= obj->scal2 / 2.0 - EPSILON)
        return (-1);
    return (0);
}

t_vec3  cylinder_norm(t_obj *obj, t_vec3 hit_point)
{
	t_vec3	normal;
	t_vec3	axis_point;
    double  hit_discs;

    hit_discs = check_discs(obj, hit_point);
    if (hit_discs)
        return (vec3_scalmult(hit_discs, obj->n));
    axis_point = vec3_add(obj->pt,
            vec3_scalmult(vec3_dot(vec3_sub(hit_point, obj->pt), obj->n),
                obj->n));
    normal = vec3_sub(hit_point, axis_point);
    vec3_normalize(&normal);
    return (normal);
}
