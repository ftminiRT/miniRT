/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_norm.c                                      :+:      :+:    :+:   */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:25:19 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:25:19 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	apply_normal_mapping(t_vec3 geo_normal, t_vec3 tangent,
		t_vec3 bitangent, t_vec3 map_normal)
{
	t_vec3	final_normal;

	final_normal.x = tangent.x * map_normal.x + bitangent.x * map_normal.y
		+ geo_normal.x * map_normal.z;
	final_normal.y = tangent.y * map_normal.x + bitangent.y * map_normal.y
		+ geo_normal.y * map_normal.z;
	final_normal.z = tangent.z * map_normal.x + bitangent.z * map_normal.y
		+ geo_normal.z * map_normal.z;
	vec3_normalize(&final_normal);
	return (final_normal);
}

t_vec3	sphere_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3		geo_normal;
	t_vec3		map_normal;
	t_normap	normap;

	geo_normal = vec3_sub(hit_point, obj->pt);
	vec3_normalize(&geo_normal);
	if (!obj->normal_map_data)
		return (geo_normal);
	normap.scale_u = 1.0;
	normap.scale_v = 1.0;
	normap.u = (atan2(geo_normal.z, geo_normal.x) / (2.0 * M_PI) + 0.5)
		* normap.scale_u;
	normap.v = (asin(geo_normal.y) / M_PI + 0.5) * normap.scale_v;
	normap.tangent = (t_vec3){-sin(2.0 * M_PI * (normap.u - 0.5)), 0, cos(2.0
			* M_PI * (normap.u - 0.5))};
	vec3_normalize(&normap.tangent);
	normap.bitangent = vec3_cross(geo_normal, normap.tangent);
	vec3_normalize(&normap.bitangent);
	map_normal = sample_normal_map(obj, normap.u, normap.v);
	return (apply_normal_mapping(geo_normal, normap.tangent, normap.bitangent,
			map_normal));
}

t_vec3	plane_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3		geo_normal;
	t_vec3		map_normal;
	t_vec3		local_pos;
	t_normap	normap;

	geo_normal = obj->n;
	if (!obj->normal_map_data)
		return (geo_normal);
	local_pos = vec3_sub(hit_point, obj->pt);
	if (fabs(geo_normal.y) < 0.9)
		normap.tangent = vec3_cross(geo_normal, (t_vec3){0, 1, 0});
	else
		normap.tangent = vec3_cross(geo_normal, (t_vec3){1, 0, 0});
	vec3_normalize(&normap.tangent);
	normap.bitangent = vec3_cross(geo_normal, normap.tangent);
	vec3_normalize(&normap.bitangent);
	normap.scale_u = 100;
	normap.scale_v = 100;
	normap.u = vec3_dot(local_pos, normap.tangent) / normap.scale_u + 0.5;
	normap.v = vec3_dot(local_pos, normap.bitangent) / normap.scale_v + 0.5;
	normap.u = normap.u - floor(normap.u);
	normap.v = normap.v - floor(normap.v);
	map_normal = sample_normal_map(obj, normap.u, normap.v);
	return (apply_normal_mapping(geo_normal, normap.tangent, normap.bitangent,
			map_normal));
}

double	check_discs(t_obj *obj, t_vec3 hit_point)
{
	double	h;
	t_vec3	base_center;
	t_vec3	from_center;

	h = vec3_dot(vec3_sub(hit_point, obj->pt), obj->n);
	base_center = vec3_add(obj->pt, vec3_scalmult(-obj->scal2 / 2.0, obj->n));
	from_center = vec3_sub(hit_point, base_center);
	if (vec3_norm(from_center) <= obj->scal && h <= -obj->scal2 / 2.0 + EPSILON)
		return (1);
	base_center = vec3_add(obj->pt, vec3_scalmult(obj->scal2 / 2.0, obj->n));
	from_center = vec3_sub(hit_point, base_center);
	if (vec3_norm(from_center) <= obj->scal && h >= obj->scal2 / 2.0 - EPSILON)
		return (-1);
	return (0);
}

t_vec3	cylinder_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3		geo_normal;
	t_vec3		map_normal;
	t_vec3		axis_point;
	double		hit_discs;
	t_normap	normap;

	hit_discs = check_discs(obj, hit_point);
	if (hit_discs)
		return (vec3_scalmult(hit_discs, obj->n));
	axis_point = vec3_add(obj->pt, vec3_scalmult(vec3_dot(vec3_sub(hit_point,
						obj->pt), obj->n), obj->n));
	geo_normal = vec3_sub(hit_point, axis_point);
	vec3_normalize(&geo_normal);
	if (!obj->normal_map_data)
		return (geo_normal);
	normap.h = vec3_dot(vec3_sub(hit_point, obj->pt), obj->n);
	normap.u = atan2(geo_normal.z, geo_normal.x) / (2.0 * M_PI) + 0.5;
	normap.v = (normap.h + obj->scal2 / 2.0) / obj->scal2;
	normap.tangent = vec3_cross(obj->n, geo_normal);
	vec3_normalize(&normap.tangent);
	normap.bitangent = obj->n;
	map_normal = sample_normal_map(obj, normap.u, normap.v);
	return (apply_normal_mapping(geo_normal, normap.tangent, normap.bitangent,
			map_normal));
}

// Normale adaptée
t_vec3	cone_normal(t_obj *obj, t_vec3 hit_point)
{
	double h = vec3_dot(vec3_sub(hit_point, obj->pt), obj->n);

	// Sur le cap bas
	if (h <= EPSILON && h >= -EPSILON)
		return vec3_scalmult(-1, obj->n);
	// Sur le cap haut
	if (fabs(h - obj->scal2) <= EPSILON)
		return obj->n;

	// Sur le côté
	t_vec3 v = vec3_sub(hit_point, obj->pt);
	t_vec3 dir = obj->n;
	t_vec3 radial = vec3_sub(v, vec3_scalmult(vec3_dot(v, dir), dir));
	double denom = vec3_dot(dir, v);
	double alpha = vec3_dot(radial, v) / denom;
	t_vec3 N = vec3_sub(radial, vec3_scalmult(alpha, dir));
	vec3_normalize(&N);
	return N;
}

// t_vec3 cone_normal(t_obj *obj, t_vec3 hit_point)
// {
//     t_vec3 v = vec3_sub(hit_point, obj->pt); // vecteur sommet → hit
//     t_vec3 dir = obj->n;                     // axe du cône (unitaire)
//     t_vec3 radial;
//     t_vec3 N;
//     double alpha;

//     // projection de v sur l'axe
//     double proj_len = vec3_dot(v, dir);
//     t_vec3 proj = vec3_scalmult(proj_len, dir);

//     // vecteur radial dans le plan du cône
//     radial = vec3_sub(v, proj);

//     // calcule alpha pour que N soit perpendiculaire à la génératrice
//     // N = radial - alpha * dir
//     // dot(N, v) = 0 → alpha = dot(radial, v) / dot(dir, v)
//     if (proj_len != 0)
//         alpha = vec3_dot(radial, v) / proj_len;
//     else
//         alpha = 0;

//     N = vec3_sub(radial, vec3_scalmult(alpha, dir));

//     vec3_normalize(&N);
//     return N;
// }
// t_vec3	cone_normal(t_obj *obj, t_vec3 hit_point)
// {
// 	t_vec3	v;
// 	double	alpha;
// 	t_vec3	ret;

// 	v = vec3_sub(hit_point, obj->pt);
// 	alpha = vec3_dot(v, obj->n);
// 	// obj->k = tan(angle) * tan(angle);
// 	// obj->n est bien normalise
// 	ret = vec3_sub(v,
// 		vec3_scalmult((1 + obj->k) * alpha, obj->n));
// 	vec3_normalize(&ret);
// 	return (ret);
// }