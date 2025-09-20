/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:27:59 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:27:59 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	local_point(t_vec3 hit_point, t_obj *obj, t_basis b)
{
	t_vec3	p;
	t_vec3	pl;

	p = vec3_sub(hit_point, obj->pt);
	pl.x = vec3_dot(p, b.u) / obj->scal;
	pl.y = vec3_dot(p, b.w) / obj->scal3;
	pl.z = vec3_dot(p, b.v) / obj->scal;
	return (pl);
}

static t_vec3	local_normal(t_vec3 pl, t_obj *obj)
{
	t_vec3	n_scaled;
	t_vec3	n_local;
	double	r;

	r = obj->scal2 / obj->scal;
	n_scaled.x = 4.0 * pl.x * (vec3_dot(pl, pl) - r * r - 1.0);
	n_scaled.y = 4.0 * pl.y * (vec3_dot(pl, pl) - r * r - 1.0 + 2.0 * r * r);
	n_scaled.z = 4.0 * pl.z * (vec3_dot(pl, pl) - r * r - 1.0);
	n_local.x = n_scaled.x / obj->scal;
	n_local.y = n_scaled.y / obj->scal3;
	n_local.z = n_scaled.z / obj->scal;
	return (n_local);
}

static t_vec3	world_normal(t_vec3 n_local, t_basis b)
{
	t_vec3	geo_normal;

	geo_normal.x = n_local.x * b.u.x + n_local.y * b.w.x + n_local.z * b.v.x;
	geo_normal.y = n_local.x * b.u.y + n_local.y * b.w.y + n_local.z * b.v.y;
	geo_normal.z = n_local.x * b.u.z + n_local.y * b.w.z + n_local.z * b.v.z;
	return (vec3_normalized(geo_normal));
}

static t_vec3	normal_with_map(t_obj *obj, t_vec3 pl, t_vec3 geo_normal,
		t_vec3 u)
{
	t_normap	normap;
	double		phi;
	double		theta;

	normap.tangent = vec3_cross(obj->n, geo_normal);
	if (vec3_norm(normap.tangent) < 1e-6)
		normap.tangent = u;
	normap.tangent = vec3_normalized(normap.tangent);
	normap.bitangent = vec3_cross(geo_normal, normap.tangent);
	phi = atan2(pl.z, pl.x);
	theta = atan2(pl.y * obj->scal, (sqrt(pl.x * pl.x + pl.z * pl.z)
				- obj->scal2 / obj->scal) * obj->scal3);
	normap.u = phi / (2.0 * M_PI) + 0.5;
	normap.v = theta / (2.0 * M_PI) + 0.5;
	return (apply_normal_mapping(geo_normal, normap.tangent, normap.bitangent,
			sample_normal_map(obj, normap.u, normap.v)));
}

t_vec3	ring_normal(t_obj *obj, t_vec3 hit_point)
{
	t_basis	b;
	t_vec3	pl;
	t_vec3	n_local;
	t_vec3	geo_normal;

	init_base(obj, &b);
	pl = local_point(hit_point, obj, b);
	n_local = local_normal(pl, obj);
	geo_normal = world_normal(n_local, b);
	if (!obj->normal_map_data)
		return (geo_normal);
	return (normal_with_map(obj, pl, geo_normal, b.u));
}
