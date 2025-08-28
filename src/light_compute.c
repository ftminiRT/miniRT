/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_compute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:26 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 14:26:54 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static t_color	compute_diffuse(t_phong phong, t_obj *obj, t_light *cur_spot)
{
	double	diff_factor;
	t_color	diffuse;

	if (obj->type == OT_PLANE)
		diff_factor = cur_spot->brightness * fabs(vec3_dot(phong.light,
					phong.normal));
	else
		diff_factor = cur_spot->brightness * fmax(0.0, vec3_dot(phong.light,
					phong.normal));
	diffuse = color_scale(color_multiply(cur_spot->color, obj->color),
			diff_factor * cur_spot->brightness);
	return (diffuse);
}

static t_color	compute_specular(t_phong phong, t_obj *obj, t_light *cur_spot)
{
	double	spec_factor;
	t_color	specular;

	phong.reflected = vec3_sub(vec3_scalmult(2.0 * fabs(vec3_dot(phong.normal,
						phong.light)), phong.normal), phong.light);
	spec_factor = 0.0;
	if (vec3_dot(phong.normal, phong.light) > 0.0)
		spec_factor = cur_spot->brightness * pow(fmax(0.0,
					vec3_dot(phong.reflected, phong.view)), obj->shine);
	specular = color_scale(cur_spot->color, spec_factor * cur_spot->brightness);
	return (specular);
}

static void	multi_spotlights(t_env *rt, t_obj *obj, t_vec3 hit_point,
		t_color *ret)
{
	t_phong	phong;
	t_color	diffuse;
	t_color	specular;
	t_light	*cur_spot;

	phong.normal = rt->get_norm[obj->type](obj, hit_point);
	phong.view = vec3_sub(rt->ray.pt, hit_point);
	vec3_normalize(&phong.view);
	cur_spot = &rt->spot;
	while (cur_spot)
	{
		if (!in_shadow(rt, cur_spot, hit_point))
		{
			phong.light = vec3_sub(cur_spot->pos, hit_point);
			vec3_normalize(&phong.light);
			vec3_normalize(&phong.reflected);
			diffuse = compute_diffuse(phong, obj, cur_spot);
			specular = compute_specular(phong, obj, cur_spot);
			*ret = color_add(*ret, diffuse);
			*ret = color_add(*ret, specular);
		}
		cur_spot = cur_spot->next;
	}
}

t_color	get_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	t_color	ambient;
	t_color	ret;

	ambient = color_scale(color_multiply(rt->ambient.color, obj->color),
			rt->ambient.brightness);
	ret = ambient;
	multi_spotlights(rt, obj, hit_point, &ret);
	return (ret);
}
