/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_torus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:53:36 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:53:36 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_r_and_zarr(double *r, double *zarr)
{
	r[0] = zarr[0];
	r[1] = zarr[1];
	r[2] = zarr[2];
	r[3] = zarr[3];
}

static void	compute_coeffs(t_ray *ray, t_obj *obj, double *a)
{
	t_basis	b;
	t_ring	to;

	to.br = obj->scal2;
	to.r = obj->scal;
	init_base(obj, &b);
	to.ro = (t_vec3){vec3_dot(vec3_sub(ray->pt, obj->pt), b.u),
		vec3_dot(vec3_sub(ray->pt, obj->pt), b.w), vec3_dot(vec3_sub(ray->pt,
				obj->pt), b.v)};
	to.rd = (t_vec3){vec3_dot(ray->dir, b.u), vec3_dot(ray->dir, b.w),
		vec3_dot(ray->dir, b.v)};
	to.dd = vec3_dot(to.rd, to.rd);
	to.e = vec3_dot(to.ro, to.ro) - (to.br * to.br + to.r * to.r);
	to.f = vec3_dot(to.ro, to.rd);
	to.four_br2 = 4.0 * to.br * to.br;
	a[0] = (to.e * to.e - to.four_br2 * (to.r * to.r - to.ro.y * to.ro.y))
		/ (to.dd * to.dd);
	a[1] = (4.0 * to.f * to.e + 2.0 * to.four_br2 * to.ro.y * to.rd.y) / (to.dd
			* to.dd);
	a[2] = (2.0 * to.dd * to.e + 4.0 * to.f * to.f + to.four_br2 * to.rd.y
			* to.rd.y) / (to.dd * to.dd);
	a[3] = (4.0 * to.dd * to.f) / (to.dd * to.dd);
}

double	hit_torus(t_ray *ray, t_obj *obj)
{
	double	a[4];
	double	roots[4];
	int		num_real_roots;

	if (!obj->scal || !obj->scal2)
		return (INFINITY);
	compute_coeffs(ray, obj, a);
	num_real_roots = solve_quartic(a, roots);
	if (num_real_roots == 0)
		return (INFINITY);
	if (num_real_roots == 2)
	{
		if (roots[0] >= 0)
			return (roots[0]);
		if (roots[1] >= 0)
			return (roots[1]);
		return (INFINITY);
	}
	num_real_roots = -1;
	while (++num_real_roots < 4)
		if (roots[num_real_roots] > 0)
			return (roots[num_real_roots]);
	return (INFINITY);
}
