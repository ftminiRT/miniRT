/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_compute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:26 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/26 15:16:27 by tbeauman         ###   ########.fr       */
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

t_color	simple_lighting(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	t_vec3 light_dir;
	double total_light;

	light_dir = vec3_sub(rt->spot.pos, hit_point);
	vec3_normalize(&light_dir);
	total_light = fmin(1.0, rt->ambient.brightness + fmax(0.0,
				vec3_dot(get_normal(obj, hit_point), light_dir))
			* rt->spot.brightness);
	return (color_scale(obj->color, total_light));
}