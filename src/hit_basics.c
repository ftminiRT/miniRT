/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:17:01 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 14:25:25 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(t_ray *ray, t_obj *s)
{
	t_proj_data	proj;
	double		hit1;
	double		hit2;
	t_vec3		oc;

	oc = vec3_sub(ray->pt, s->pt);
	proj.b = vec3_dot(oc, ray->dir);
	proj.c = vec3_dot(oc, oc) - s->scal * s->scal;
	proj.delta = proj.b * proj.b - proj.c;
	if (proj.delta < 0)
		return (INFINITY);
	proj.sqrt_d = sqrt(proj.delta);
	hit1 = -proj.b - proj.sqrt_d;
	hit2 = -proj.b + proj.sqrt_d;
	if (hit1 > EPSILON)
		return (hit1);
	if (hit2 > EPSILON)
		return (hit2);
	return (INFINITY);
}

double	hit_plane(t_ray *r, t_obj *p)
{
	double	a;
	double	b;
	double	t;

	a = vec3_dot(r->dir, p->n);
	b = vec3_dot(p->n, vec3_sub(r->pt, p->pt));
	if (fabs(a) < EPSILON)
		return (INFINITY);
	t = -b / a;
	if (t < EPSILON)
		return (INFINITY);
	return (t);
}
