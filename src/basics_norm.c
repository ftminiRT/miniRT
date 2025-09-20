/* ************************************************************************** */
/*                                                       :::      ::::::::   */
/*   basics_norm.c (avec normal mapping)                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:25:56 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/02 XX:XX:XX by tbeauman         ###   ########.fr       */
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

t_vec3 cone_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3	tmp;
	t_vec3	ret;
	double	angle;
	double	k;

	angle = (obj->scal * M_PI) / 180.0;
	k = 1.0 + (tan(angle) * tan(angle));

	tmp = vec3_sub(hit_point, obj->pt);
	ret.x = 2 * tmp.x;
	ret.y = 2 * tmp.y;
	ret.z = 2 * (tmp.z) - 2 * k * vec3_dot(tmp, obj->n) * obj->n.z;
	vec3_normalize(&ret);
	return (ret);
}