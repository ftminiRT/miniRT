/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:52:59 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:52:59 by tcoeffet         ###   ########.fr       */
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
