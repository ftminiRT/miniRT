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

// Appliquer le normal mapping avec la matrice TBN
t_vec3	apply_normal_mapping(t_vec3 geo_normal, t_vec3 tangent, t_vec3 bitangent, t_vec3 map_normal)
{
	t_vec3	final_normal;
	
	// Transformer de tangent space vers world space
	final_normal.x = tangent.x * map_normal.x + bitangent.x * map_normal.y + geo_normal.x * map_normal.z;
	final_normal.y = tangent.y * map_normal.x + bitangent.y * map_normal.y + geo_normal.y * map_normal.z;
	final_normal.z = tangent.z * map_normal.x + bitangent.z * map_normal.y + geo_normal.z * map_normal.z;
	
	vec3_normalize(&final_normal);
	return (final_normal);
}

t_vec3	sphere_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3	geo_normal;
	t_vec3	tangent, bitangent;
	t_vec3	map_normal;
	float	u, v;

	// Normale géométrique
	geo_normal = vec3_sub(hit_point, obj->pt);
	vec3_normalize(&geo_normal);
	
	// Si pas de normal mapping, retourner la normale géométrique
	if (!obj->normal_map_data)
		return (geo_normal);
	
	// Calculer les coordonnées UV sphériques
	u = atan2(geo_normal.z, geo_normal.x) / (2.0 * M_PI) + 0.5;
	v = asin(geo_normal.y) / M_PI + 0.5;
	
	// Calculer le vecteur tangent (dérivée par rapport à u)
	tangent = (t_vec3){-sin(2.0 * M_PI * (u - 0.5)), 0, cos(2.0 * M_PI * (u - 0.5))};
	vec3_normalize(&tangent);
	
	// Calculer le bitangent
	bitangent = vec3_cross(geo_normal, tangent);
	vec3_normalize(&bitangent);
	
	// Sampler la normal map
	map_normal = sample_normal_map(obj, u, v);
	
	// Appliquer le normal mapping
	return (apply_normal_mapping(geo_normal, tangent, bitangent, map_normal));
}

t_vec3	plane_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3	geo_normal;
	t_vec3	tangent, bitangent;
	t_vec3	map_normal;
	t_vec3	local_pos;
	float	u, v;
	
	geo_normal = obj->n;
	
	// Si pas de normal mapping, retourner la normale géométrique
	if (!obj->normal_map_data)
		return (geo_normal);
	
	// Position locale sur le plan
	local_pos = vec3_sub(hit_point, obj->pt);
	
	// Créer une base orthonormée pour le plan
	if (fabs(geo_normal.y) < 0.9)
		tangent = vec3_cross(geo_normal, (t_vec3){0, 1, 0});
	else
		tangent = vec3_cross(geo_normal, (t_vec3){1, 0, 0});
	vec3_normalize(&tangent);
	
	bitangent = vec3_cross(geo_normal, tangent);
	vec3_normalize(&bitangent);
	
	// Calculer les coordonnées UV

	double	text_scal = obj->scal == 0 ? 10 : obj->scal;
	u = vec3_dot(local_pos, tangent) / text_scal + 0.5; // scal = taille du plan
	v = vec3_dot(local_pos, bitangent) / text_scal + 0.5;
	
	// Répéter la texture
	u = u - floor(u);
	v = v - floor(v);
	
	// Sampler la normal map
	map_normal = sample_normal_map(obj, u, v);
	
	// Appliquer le normal mapping
	return (apply_normal_mapping(geo_normal, tangent, bitangent, map_normal));
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
	t_vec3	geo_normal;
	t_vec3	tangent, bitangent;
	t_vec3	map_normal;
	t_vec3	axis_point;
	double	hit_discs;
	float	u, v, h;

	hit_discs = check_discs(obj, hit_point);
	
	// Pour les bouchons du cylindre (pas de normal mapping sur les disques)
	if (hit_discs)
		return (vec3_scalmult(hit_discs, obj->n));
	
	// Normale géométrique de la surface cylindrique
	axis_point = vec3_add(obj->pt, vec3_scalmult(vec3_dot(vec3_sub(hit_point,
						obj->pt), obj->n), obj->n));
	geo_normal = vec3_sub(hit_point, axis_point);
	vec3_normalize(&geo_normal);
	
	// Si pas de normal mapping, retourner la normale géométrique
	if (!obj->normal_map_data)
		return (geo_normal);
	
	// Calculer les coordonnées UV cylindriques
	h = vec3_dot(vec3_sub(hit_point, obj->pt), obj->n);
	u = atan2(geo_normal.z, geo_normal.x) / (2.0 * M_PI) + 0.5;
	v = (h + obj->scal2 / 2.0) / obj->scal2; // scal2 = hauteur
	
	// Calculer tangent (direction circumférentielle)
	tangent = vec3_cross(obj->n, geo_normal);
	vec3_normalize(&tangent);
	
	// Bitangent = axe du cylindre
	bitangent = obj->n;
	
	// Sampler la normal map
	map_normal = sample_normal_map(obj, u, v);
	
	// Appliquer le normal mapping
	return (apply_normal_mapping(geo_normal, tangent, bitangent, map_normal));
}