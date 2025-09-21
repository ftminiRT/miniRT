/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-21 10:19:36 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-21 10:19:36 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	cone_geo_normal(t_obj *obj, t_vec3 hit_point)
{
	double	h;
	double	denom;
	double	alpha;
	t_vec3	v;
	t_vec3	radial;

	h = vec3_dot(vec3_sub(hit_point, obj->pt), obj->n);
	if (h <= EPSILON && h >= -EPSILON)
		return (vec3_scalmult(-1, obj->n));
	if (fabs(h - obj->scal2) <= EPSILON)
		return (obj->n);
	v = vec3_sub(hit_point, obj->pt);
	radial = vec3_sub(v, vec3_scalmult(vec3_dot(v, obj->n), obj->n));
	denom = vec3_dot(obj->n, v);
	alpha = vec3_dot(radial, v) / denom;
	return (vec3_normalized(vec3_sub(radial, vec3_scalmult(alpha, obj->n))));
}

static void	get_tbn(t_obj *obj, t_vec3 hit_point, t_vec3 geo_normal,
		t_normap *normap)
{
	if (fabs(geo_normal.x) < 0.9)
		normap->tangent = vec3_cross(geo_normal, (t_vec3){1, 0, 0});
	else
		normap->tangent = vec3_cross(geo_normal, (t_vec3){0, 1, 0});
	vec3_normalize(&normap->tangent);
	normap->bitangent = vec3_cross(geo_normal, normap->tangent);
	vec3_normalize(&normap->bitangent);
	normap->h = vec3_dot(vec3_sub(hit_point, vec3_sub(obj->pt,
					vec3_scalmult(obj->scal2, obj->n))), obj->n);
}

static void	get_normap_uv(t_obj *obj, t_vec3 hit_point, t_normap *normap)
{
	t_vec3	local;
	t_vec3	radial;

	if (normap->h >= obj->scal2 - EPSILON)
	{
		local = vec3_sub(hit_point, obj->pt);
		normap->u = (vec3_dot(local, normap->tangent) / obj->scal + 1.0) * 0.5;
		normap->v = (vec3_dot(local, normap->bitangent) / obj->scal + 1.0)
			* 0.5;
	}
	else
	{
		radial = vec3_sub(vec3_sub(hit_point, vec3_sub(obj->pt,
						vec3_scalmult(obj->scal2, obj->n))),
				vec3_scalmult(vec3_dot(vec3_sub(hit_point, vec3_sub(obj->pt,
								vec3_scalmult(obj->scal2, obj->n))), obj->n),
					obj->n));
		normap->u = atan2(vec3_dot(radial, normap->bitangent), vec3_dot(radial,
					normap->tangent)) / (2.0 * M_PI) + 0.5;
		normap->v = normap->h / obj->scal2;
	}
}

t_vec3	cone_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3		geo_normal;
	t_vec3		map_normal;
	t_normap	normap;

	geo_normal = cone_geo_normal(obj, hit_point);
	if (!obj->normal_map_data)
		return (geo_normal);
	get_tbn(obj, hit_point, geo_normal, &normap);
	get_normap_uv(obj, hit_point, &normap);
	map_normal = sample_normal_map(obj, normap.u, normap.v);
	return (apply_normal_mapping(geo_normal, normap.tangent, normap.bitangent,
			map_normal));
}
