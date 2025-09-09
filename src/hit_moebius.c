/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_moebius.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:44:09 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 19:47:16 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	inside_moebius(t_obj *m, t_vec3 h)
{
	double	t;
	double	s;

	t = atan2(h.y, h.x);
	if (dblsgn(sin(t / 2)) != 0)
		s = h.z / sin(t / 2);
	else
		s = (h.x / cos(t) - m->scal) / cos(t / 2) * dblsgn(cos(t)) + (h.y
				/ sin(t) - m->scal) / cos(t / 2) * !dblsgn(cos(t));
	h.x -= (m->scal + s * cos(t / 2)) * cos(t);
	h.y -= (m->scal + s * cos(t / 2)) * sin(t);
	h.z -= s * sin(t / 2);
	if (dblsgn(h.x * h.x + h.y * h.y + h.z * h.z))
		return (0);
	return (s >= -m->max && s <= m->max);
}

static double	choose_mobi_root(double *roots, int ret, t_ray *ray, t_obj *obj)
{
	int		i;
	t_vec3	hit;

	i = 0;
	while (i < ret)
	{
		if (roots[i] > EPSILON)
		{
			hit = vec3_add(vec3_scalmult(roots[i], ray->dir), ray->pt);
			if (inside_moebius(obj, hit))
				return (roots[i]);
		}
		i++;
	}
	return (INFINITY);
}

static void	init_coeffs(t_moebius m, double *coeff)
{
	coeff[3] = m.c * m.c * m.e + m.e * m.e * m.e - 2 * m.c * m.c * m.g - 2 * m.e
		* m.e * m.g + m.e * m.g * m.g;
	coeff[0] = (m.b * m.b * m.d + m.d * m.d * m.d - 2 * m.b * m.b * m.f - 2
			* m.d * m.d * m.f + m.d * m.f * m.f - 2 * m.b * m.f * m.a - m.d
			* m.a * m.a) / coeff[3];
	coeff[1] = (m.e * m.b * m.b - 2 * m.g * m.b * m.b + 2 * m.c * m.b * m.d + 3
			* m.e * m.d * m.d - 2 * m.g * m.d * m.d - 4 * m.c * m.b * m.f - 4
			* m.e * m.d * m.f + 2 * m.g * m.d * m.f + m.e * m.f * m.f - 2 * m.g
			* m.b * m.a - 2 * m.c * m.f * m.a - m.e * m.a * m.a) / coeff[3];
	coeff[2] = (2 * m.c * m.e * m.b - 4 * m.c * m.g * m.b + m.c * m.c * m.d + 3
			* m.e * m.e * m.d - 4 * m.e * m.g * m.d + m.g * m.g * m.d - 2 * m.c
			* m.c * m.f - 2 * m.e * m.e * m.f + 2 * m.e * m.g * m.f - 2 * m.c
			* m.g * m.a) / coeff[3];
}

double	hit_moebius(t_ray *ray, t_obj *obj)
{
	double		a[4];
	double		root[3];
	t_basis		b;
	t_moebius	m;
	t_ray		local_ray;

	b = make_basis(obj->n);
	local_ray = world_to_local_ray(*ray, obj, b);
	m.a = obj->scal;
	m.b = local_ray.pt.x;
	m.c = local_ray.dir.x;
	m.d = local_ray.pt.y;
	m.e = local_ray.dir.y;
	m.f = local_ray.pt.z;
	m.g = local_ray.dir.z;
	init_coeffs(m, a);
	return (choose_mobi_root(root, solve_cubic(a, root), &local_ray, obj));
}

// t_vec3	moebius_normal(t_obj *obj, t_vec3 hit_point, t_env *rt)
// {
// 	t_vec3		geo_normal;
// 	t_vec3		tangent;
// 	t_vec3		bitangent;
// 	t_vec3		map_normal;
// 	t_normap	normap;

// 	// Version minimale basée sur votre original
// 	geo_normal = vec3_sub(hit_point, obj->pt);
// 	// Ajouter un petit facteur de torsion
// 	double angle = atan2(hit_point.y, hit_point.x);
// 	geo_normal.z += sin(angle/2); // facteur de torsion léger
// 	vec3_normalize(&geo_normal);
// 	if (!obj->normal_map_data || rt->basicrt)
// 		return (geo_normal);
// 	tangent = (t_vec3){-geo_normal.y, geo_normal.x, 0};
// 	vec3_normalize(&tangent);
// 	bitangent = vec3_cross(geo_normal, tangent);
// 	normap.u = atan2(hit_point.y, hit_point.x) / (2.0 * M_PI) + 0.5;
// 	normap.v = 0.5 + hit_point.z / obj->scal;
// 	map_normal = sample_normal_map(obj, normap.u, normap.v);
// 	return (apply_normal_mapping(geo_normal, tangent, bitangent, map_normal));
// }
