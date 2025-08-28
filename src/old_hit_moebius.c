/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_moebius.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:29:31 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 19:40:27 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				dblsgn(double x)
{
	if (x < -EPSILON)
		return (-1);
	return (x > EPSILON);
}

int				inside(t_obj *m, t_vec3 h)
{
	double t;
	double s;

	t = atan2(h.y, h.x);
	if (dblsgn(sin(t / 2)) != 0)
		s = h.z / sin(t / 2);
	else
		s = dblsgn(cos(t)) ? (h.x / cos(t) - m->scal) / cos(t / 2) :
			(h.y / sin(t) - m->scal) / cos(t / 2);
	h.x -= (m->scal + s * cos(t / 2)) * cos(t);
	h.y -= (m->scal + s * cos(t / 2)) * sin(t);
	h.z -= s * sin(t / 2);
	if (dblsgn(h.x * h.x + h.y * h.y + h.z * h.z))
		return (0);
	return (s >= -m->max && s <= m->max);
}

static double	choose_mobi_root(double *roots, int ret, t_ray *ray, t_obj *obj)
{
	int			i;
	t_vec3		hit;

	i = 0;
	while (i < ret)
	{
		if (roots[i] > EPSILON)
		{
			hit = vec3_add(vec3_scalmult(roots[i], ray->dir), ray->pt);
			if (inside(obj, hit))
				return (roots[i]);
		}
		i++;
	}
	return (INFINITY);
}

static void		init_coeffs(t_moebius m, double *coeff)
{
	coeff[3] = m.c * m.c * m.e + m.e * m.e * m.e - 2 * m.c * m.c * m.g - 2 * m.e
		* m.e * m.g + m.e * m.g * m.g;
	coeff[0] = (m.b * m.b * m.d + m.d * m.d * m.d - 2 * m.b * m.b * m.f - 2 *
		m.d * m.d * m.f
		+ m.d * m.f * m.f - 2 * m.b * m.f * m.a - m.d * m.a * m.a) / coeff[3];
	coeff[1] = (m.e * m.b * m.b - 2 * m.g * m.b * m.b + 2 * m.c * m.b * m.d + 3
		* m.e * m.d
		* m.d - 2 * m.g * m.d * m.d - 4 * m.c * m.b * m.f - 4 * m.e * m.d * m.f
		+ 2 * m.g * m.d
		* m.f + m.e * m.f * m.f - 2 * m.g * m.b * m.a - 2 * m.c * m.f * m.a -
		m.e * m.a * m.a) / coeff[3];
	coeff[2] = (2 * m.c * m.e * m.b - 4 * m.c * m.g * m.b + m.c * m.c * m.d + 3
		* m.e * m.e
		* m.d - 4 * m.e * m.g * m.d + m.g * m.g * m.d - 2 * m.c * m.c * m.f -
		2 * m.e * m.e * m.f
		+ 2 * m.e * m.g * m.f - 2 * m.c * m.g * m.a) / coeff[3];
}

double			hit_moebius(t_ray *ray, t_obj *obj)
{
	double		a[4];
	double		root[3];
	t_moebius	m;
	t_vec3		x;
	int			ret;


	x = ray->pt;
	m.a = obj->scal;
	m.b = x.x;
	m.c = ray->dir.x;
	m.d = x.y;
	m.e = ray->dir.y;
	m.f = x.z;
	m.g = ray->dir.z;
	init_coeffs(m, a);
	ret = solve_cubic(a, root);
	return (choose_mobi_root(root, ret, ray, obj));
}

t_vec3			moebius_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3	ret;

    ret.x = -2 * obj->scal * hit_point.z + 2 * hit_point.x * hit_point.y - 4 * hit_point.x *
		hit_point.z;
	ret.y = -obj->scal2 + hit_point.x * hit_point.x + 3 * hit_point.y * hit_point.y - 4
		* hit_point.y * hit_point.z + hit_point.z * hit_point.z;
	ret.z = -2 * obj->scal * hit_point.x - 2 * hit_point.x * hit_point.x - 2 * hit_point.y *
		hit_point.y + 2 * hit_point.y * hit_point.z;
    vec3_normalize(&ret);
    return (ret);
}
