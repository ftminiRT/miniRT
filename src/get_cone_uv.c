/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-21 10:31:31 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-21 10:31:31 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_cone_radial(t_obj *obj, t_vec3 hit_point)
{
	return (vec3_sub(hit_point,
			vec3_add(vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n)),
				vec3_scalmult(vec3_dot(vec3_sub(hit_point,
							vec3_sub(obj->pt, vec3_scalmult(obj->scal2,
									obj->n))), obj->n), obj->n))));
}

static void	get_cone_body_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3		rad;
	t_basis		b;
	t_normap	nmap;

	rad = get_cone_radial(obj, hit_point);
	b = make_basis(obj->n);
	nmap.u = atan2(vec3_dot(rad, b.v), vec3_dot(rad, b.u)) / (2.0 * M_PI) + 0.5;
	nmap.v = vec3_dot(vec3_sub(hit_point,
				vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))), obj->n)
		/ obj->scal2;
	if (obj->checkered)
	{
		map[0] = (int)floor(nmap.u * 10.0) % 10;
		map[1] = (int)floor(nmap.v * 10.0);
		if (map[0] < 0)
			map[0] += 10;
	}
	else
	{
		map[0] = ((int)floor(nmap.u * obj->texture_w) % obj->texture_w
				+ obj->texture_w) % obj->texture_w;
		map[1] = ((int)floor(nmap.v * obj->texture_h) % obj->texture_h
				+ obj->texture_h) % obj->texture_h;
	}
}

static void	get_cone_cap_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	local;

	local = vec3_sub(hit_point, obj->pt);
	if (obj->checkered)
	{
		map[0] = ((int)floor((local.x / obj->scal + 1.0) * 5.0) % 10 + 10) % 10;
		map[1] = ((int)floor((local.z / obj->scal + 1.0) * 5.0) % 10 + 10) % 10;
	}
	else
	{
		map[0] = ((int)floor((local.x / obj->scal + 1.0) * 0.5 * obj->texture_w)
				% obj->texture_w + obj->texture_w) % obj->texture_w;
		map[1] = ((int)floor((local.z / obj->scal + 1.0) * 0.5 * obj->texture_h)
				% obj->texture_h + obj->texture_h) % obj->texture_h;
	}
}

void	get_cone_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	from_center;
	double	h;

	from_center = vec3_sub(hit_point, obj->pt);
	h = vec3_dot(from_center, obj->n);
	if (h >= 0 && h <= obj->scal2 - EPSILON)
		get_cone_body_uv(obj, hit_point, map);
	else
		get_cone_cap_uv(obj, hit_point, map);
}
