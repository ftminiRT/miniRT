/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moebius_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:48:22 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:48:22 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	moebius_local_coords(t_obj *obj, t_vec3 hit_point, t_basis b,
		t_moebnorm *comp)
{
	t_vec3	local_hit;
	t_vec3	rel;

	rel = vec3_sub(hit_point, obj->pt);
	local_hit = world_to_local_vec(rel, b);
	comp->t = atan2(local_hit.y, local_hit.x);
	if (fabs(sin(comp->t / 2)) > EPSILON)
		comp->s = local_hit.z / sin(comp->t / 2);
	else
		comp->s = (local_hit.x / cos(comp->t) - obj->scal) / cos(comp->t / 2);
	return (local_hit);
}

static void	moebius_derivatives(t_obj *obj, t_moebnorm *comp)
{
	comp->dp_dt = (t_vec3){(-1 * (obj->scal + comp->s * cos(comp->t / 2)))
		* sin(comp->t) - 0.5 * comp->s * sin(comp->t / 2) * cos(comp->t),
		(obj->scal + comp->s * cos(comp->t / 2)) * cos(comp->t) - 0.5 * comp->s
		* sin(comp->t / 2) * sin(comp->t), 0.5 * comp->s * cos(comp->t / 2)};
	comp->dp_ds = (t_vec3){cos(comp->t / 2) * cos(comp->t), cos(comp->t / 2)
		* sin(comp->t), sin(comp->t / 2)};
}

static t_vec3	moebius_geo_normal(t_moebnorm *comp, t_basis b)
{
	t_vec3	geo_normal;

	geo_normal = vec3_cross(comp->dp_dt, comp->dp_ds);
	vec3_normalize(&geo_normal);
	geo_normal = local_to_world_vec(geo_normal, b);
	return (geo_normal);
}

static t_vec3	moebius_apply_normal_mapping(t_obj *obj,
		t_vec3 geo_normal, t_moebnorm comp)
{
	t_normap	normap;

	if (!obj->normal_map_data)
		return (geo_normal);
	normap.tangent = local_to_world_vec(comp.dp_dt, make_basis(obj->n));
	vec3_normalize(&normap.tangent);
	normap.bitangent = vec3_cross(geo_normal, normap.tangent);
	vec3_normalize(&normap.bitangent);
	normap.u = (comp.t + M_PI) / (2.0 * M_PI);
	normap.v = (comp.s / obj->max + 1.0) * 0.5;
	if (normap.u >= 1.0)
		normap.u -= 1.0;
	normap.v = fmax(0.0, fmin(1.0, normap.v));
	return (apply_normal_mapping(geo_normal, normap.tangent, normap.bitangent,
			sample_normal_map(obj, normap.u, normap.v)));
}

t_vec3	moebius_normal(t_obj *obj, t_vec3 hit_point)
{
	t_moebnorm	comp;
	t_basis		b;
	t_vec3		geo_normal;

	b = make_basis(obj->n);
	moebius_local_coords(obj, hit_point, b, &comp);
	moebius_derivatives(obj, &comp);
	geo_normal = moebius_geo_normal(&comp, b);
	return (moebius_apply_normal_mapping(obj, geo_normal, comp));
}
