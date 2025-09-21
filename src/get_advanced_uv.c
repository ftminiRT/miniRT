/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_advanced_uv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:47:43 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:47:43 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_torus_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	rel;
	double	u;
	double	v;
	double	theta;

	rel = vec3_sub(hit_point, obj->pt);
	theta = atan2(rel.z, rel.x);
	if (theta < 0)
		theta += 2.0 * M_PI;
	u = theta / (2.0 * M_PI);
	v = (vec3_dot(rel, obj->n) + obj->scal2) / (2.0 * obj->scal2);
	if (!obj->checkered)
	{
		map[0] = (int)floor(u * obj->texture_w);
		map[1] = (int)floor(v * obj->texture_h);
	}
	else
	{
		map[0] = (int)floor(u * 10);
		map[1] = (int)floor(v * 10);
	}
}

static void	compute_moebius_uv(t_obj *obj, t_vec3 local_hit, double uv[2])
{
	double	t;
	double	s;

	t = atan2(local_hit.y, local_hit.x);
	if (t < 0)
		t += 2.0 * M_PI;
	if (fabs(sin(t / 2)) > EPSILON)
		s = local_hit.z / sin(t / 2);
	else
		s = (local_hit.x / cos(t) - obj->scal) / cos(t / 2);
	uv[0] = fmax(0.0, fmin(0.999999, t / (2.0 * M_PI)));
	uv[1] = fmax(0.0, fmin(0.999999, (s / obj->max + 1.0) * 0.5));
}

void	get_moebius_uv(t_obj *obj, t_vec3 p, int map[2])
{
	t_basis	b;
	t_vec3	local_hit;
	double	uv[2];

	b = make_basis(obj->n);
	local_hit = world_to_local_vec(vec3_sub(p, obj->pt), b);
	compute_moebius_uv(obj, local_hit, uv);
	if (!obj->checkered)
	{
		map[0] = (int)floor(uv[0] * obj->texture_w);
		map[1] = (int)floor(uv[1] * obj->texture_h);
	}
	else
	{
		map[0] = (int)floor(uv[0] * 10);
		map[1] = (int)floor(uv[1] * 5);
	}
}
