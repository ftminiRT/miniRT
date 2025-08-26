#include "minirt.h"

t_color color_add(t_color c1, t_color c2)
{
    t_color result;
 
    result.r = (unsigned char)fmin(255, (int)c1.r + (int)c2.r);
    result.g = (unsigned char)fmin(255, (int)c1.g + (int)c2.g);
    result.b = (unsigned char)fmin(255, (int)c1.b + (int)c2.b);
    return result;
}

t_color color_scale(t_color c, double factor)
{
    t_color result;

    result.r = (unsigned char)fmin(255, (int)(c.r * factor));
    result.g = (unsigned char)fmin(255, (int)(c.g * factor));
    result.b = (unsigned char)fmin(255, (int)(c.b * factor));
    return result;
}

t_color	calc_ambient(t_color base, t_color amb, double bright)
{
	t_color	ambient;
	t_color	amb_scaled;

	amb_scaled = color_scale(amb, bright);
	ambient.r = (unsigned char)((base.r * amb_scaled.r) / 255);
	ambient.g = (unsigned char)((base.g * amb_scaled.g) / 255);
	ambient.b = (unsigned char)((base.b * amb_scaled.b) / 255);
	return (ambient);
}

t_color	calc_diffuse_spec(t_env *rt, t_obj *obj,
		t_vec3 normal, t_vec3 view_dir, t_vec3 hit_point)
{
	t_vec3	light_dir;
	double	light_distance;
	double	spec;
	t_color	spot_light;
	t_color	diffuse;
	t_vec3	reflect_dir;

	light_dir = vec3_sub(rt->spot.pos, hit_point);
	light_distance = vec3_norm(light_dir);
	vec3_normalize(&light_dir);
	reflect_dir = vec3_sub(vec3_scalmult(2.0 * vec3_dot(normal, light_dir),
				normal), light_dir);
	vec3_normalize(&reflect_dir);
	spec = pow(fmax(0.0, vec3_dot(reflect_dir, view_dir)), 32.0);
	spot_light = color_scale(rt->spot.color, rt->spot.brightness * (1.0 / (1.0 + 0.09 * light_distance + 0.032 * light_distance
			* light_distance)));
	diffuse.r = (unsigned char)((obj->color.r * spot_light.r * fmax(0.0, vec3_dot(normal, light_dir))) / 255);
	diffuse.g = (unsigned char)((obj->color.g * spot_light.g * fmax(0.0, vec3_dot(normal, light_dir))) / 255);
	diffuse.b = (unsigned char)((obj->color.b * spot_light.b * fmax(0.0, vec3_dot(normal, light_dir))) / 255);
	return (color_add(diffuse, color_scale(spot_light, spec * 0.5)));
}
