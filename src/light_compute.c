/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_compute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:26 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/27 13:42:54 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3	normal;
	t_vec3	axis_point;

	if (obj->type == OT_SPHERE)
	{
		normal = vec3_sub(hit_point, obj->pt);
		vec3_normalize(&normal);
	}
	else if (obj->type == OT_PLANE)
		normal = obj->n;
	else if (obj->type == OT_CYL)
	{
		axis_point = vec3_add(obj->pt,
				vec3_scalmult(vec3_dot(vec3_sub(hit_point, obj->pt), obj->n),
					obj->n));
		normal = vec3_sub(hit_point, axis_point);
		vec3_normalize(&normal);
	}
	else
		normal = (t_vec3){INFINITY, INFINITY, INFINITY};
	return (normal);
}
/*
bool	in_shadow(t_env *rt, t_vec3 hit_point)
{
	t_ray	light_ray;
	t_ray	og_ray;
	t_obj	*hit;
	double	light_dist;
	
	light_ray.dir = vec3_sub(rt->spot.pos, hit_point);
	light_dist = vec3_norm(light_ray.dir);
	vec3_normalize(&light_ray.dir);
	light_ray.pt = vec3_add(hit_point, vec3_scalmult(EPSILON, light_ray.dir));

	og_ray = rt->ray;
	rt->ray = light_ray;

	hit = compute_intersections(rt, &light_ray);

	if (hit && (light_ray.hit > EPSILON && light_ray.hit < light_dist))
	{
		rt->ray = og_ray;
		return (true);
	}
	rt->ray = og_ray;
	return (false);
}


t_color	get_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	t_vec3	normal;
	t_vec3	light;
	t_vec3	view;
	t_vec3	reflected;
	t_color	ambient;
	t_color	diffuse;
	double	diff_factor;
	t_color	specular;
	double	spec_factor;

	normal = get_normal(obj, hit_point);
	light = vec3_sub(rt->spot.pos, hit_point);
	vec3_normalize(&light);
	view = vec3_sub(rt->ray.pt, hit_point);
	vec3_normalize(&view);
	reflected = vec3_sub(
		vec3_scalmult(2.0 * fabs(vec3_dot(normal, light)), normal),
		 light);
	vec3_normalize(&reflected);
	ambient = color_scale(color_multiply(rt->ambient.color, obj->color), rt->ambient.brightness);

	if (in_shadow(rt, hit_point))
		return (ambient);

	if (obj->type == OT_PLANE)
		diff_factor = rt->spot.brightness * fabs(vec3_dot(light, normal));
	else
		diff_factor = rt->spot.brightness * fmax(0.0, vec3_dot(light, normal));

	diffuse = color_scale(color_multiply(rt->spot.color, obj->color), diff_factor * rt->spot.brightness);

	spec_factor = 0.0;
	if (vec3_dot(normal, light) > 0.0)
		spec_factor = rt->spot.brightness *
			pow(fmax(0.0, vec3_dot(reflected, view)), obj->shine);
	specular = color_scale(rt->spot.color, spec_factor * rt->spot.brightness);

	t_color	ret;

	ret = color_add(ambient,
			color_add(diffuse, specular));

	return (ret);
}
*/

bool	in_shadow(t_env *rt, t_light *spot, t_vec3 hit_point)
{
	t_ray	light_ray;
	t_ray	og_ray;
	t_obj	*hit;
	double	light_dist;
	
	light_ray.dir = vec3_sub(spot->pos, hit_point);
	light_dist = vec3_norm(light_ray.dir);
	vec3_normalize(&light_ray.dir);
	light_ray.pt = vec3_add(hit_point, vec3_scalmult(EPSILON, light_ray.dir));

	og_ray = rt->ray;
	rt->ray = light_ray;

	hit = compute_intersections(rt, &light_ray);

	if (hit && (light_ray.hit > EPSILON && light_ray.hit < light_dist))
	{
		rt->ray = og_ray;
		return (true);
	}
	rt->ray = og_ray;
	return (false);
}


t_color	get_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	t_vec3	normal;
	t_vec3	light;
	t_vec3	view;
	t_vec3	reflected;
	t_color	ambient;
	t_color	diffuse;
	double	diff_factor;
	t_color	specular;
	double	spec_factor;
	t_color	ret;

	normal = get_normal(obj, hit_point);
	light = vec3_sub(rt->spot.pos, hit_point);
	vec3_normalize(&light);
	view = vec3_sub(rt->ray.pt, hit_point);
	vec3_normalize(&view);
	reflected = vec3_sub(
		vec3_scalmult(2.0 * fabs(vec3_dot(normal, light)), normal),
		 light);
	vec3_normalize(&reflected);


	ambient = color_scale(color_multiply(rt->ambient.color, obj->color), rt->ambient.brightness);
	ret = ambient;
	
	t_light	*cur_spot;

	cur_spot = &rt->spot;
	while (cur_spot)
	{
		if (!in_shadow(rt, cur_spot, hit_point))
		{

			if (obj->type == OT_PLANE)
				diff_factor = cur_spot->brightness * fabs(vec3_dot(light, normal));
			else
				diff_factor = cur_spot->brightness * fmax(0.0, vec3_dot(light, normal));

			diffuse = color_scale(color_multiply(cur_spot->color, obj->color), diff_factor * cur_spot->brightness);

			spec_factor = 0.0;
			if (vec3_dot(normal, light) > 0.0)
				spec_factor = cur_spot->brightness *
					pow(fmax(0.0, vec3_dot(reflected, view)), obj->shine);
			specular = color_scale(cur_spot->color, spec_factor * cur_spot->brightness);

			ret = color_add(ret, diffuse);
			ret = color_add(ret, specular);
		}
		cur_spot = cur_spot->next;
	}
	return (ret);
}
