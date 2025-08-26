#include "minirt.h"

t_vec3 get_normal(t_obj *obj, t_vec3 hit_point)
{
    t_vec3 normal;
    
    if (obj->type == OT_SPHERE)
    {
        normal = vec3_sub(hit_point, obj->pt);
        vec3_normalize(&normal);
    }
    else if (obj->type == OT_PLANE)
        normal = obj->n;
    else if (obj->type == OT_CYL)
    {
        t_vec3 axis_point = vec3_add(obj->pt, 
                           vec3_scalmult(vec3_dot(
                            vec3_sub(hit_point, obj->pt), obj->n),
                              obj->n));
        normal = vec3_sub(hit_point, axis_point);
        vec3_normalize(&normal);
    }
    else
        normal = (t_vec3){INFINITY, INFINITY, INFINITY};
    return normal;
}

static int	in_shadow(t_env *rt, t_vec3 hit_point, t_vec3 normal,
		double *light_distance)
{
	t_ray	shadow_ray;
	t_obj	*shadow_obj;

	shadow_ray.pt = vec3_add(hit_point, vec3_scalmult(0.001, normal));
	shadow_ray.dir = vec3_sub(rt->spot.pos, hit_point);
	*light_distance = vec3_norm(shadow_ray.dir);
	vec3_normalize(&shadow_ray.dir);
	shadow_ray.hit = INFINITY;
	shadow_obj = compute_intersections(rt, &shadow_ray);
	if (shadow_obj && shadow_ray.hit < *light_distance - 0.001)
		return (1);
	return (0);
}

t_color	calculate_lighting(t_env *rt, t_obj *obj,
		t_vec3 hit_point, t_vec3 ray_dir)
{
	t_vec3	normal;
	t_vec3	view_dir;
	t_color	final_color;
	t_color	ambient;
	double	light_distance;

	normal = get_normal(obj, hit_point);
	view_dir = vec3_scalmult(-1.0, ray_dir);
	vec3_normalize(&view_dir);
	ambient = calc_ambient(obj->color, rt->ambient.color,
			rt->ambient.brightness);
	final_color = ambient;
	if (!in_shadow(rt, hit_point, normal, &light_distance))
		final_color = color_add(final_color,
				calc_diffuse_spec(rt, obj, normal, view_dir, hit_point));
	return (final_color);
}

t_color simple_lighting(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
    t_vec3 light_dir;
    double total_light;

    light_dir = vec3_sub(rt->spot.pos, hit_point);
    vec3_normalize(&light_dir);
    total_light = fmin(1.0, rt->ambient.brightness + 
        fmax(0.0, vec3_dot(get_normal(obj, hit_point), light_dir)) * rt->spot.brightness);
    return (color_scale(obj->color, total_light));
}