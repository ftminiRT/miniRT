/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-10 14:40:22 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-10 14:40:22 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	compute_coefs_cone(t_ray *r, t_obj *obj, double *arg)
{
	t_vec3	co;
	double	rada;

	rada = obj->scal * M_PI / 180;
	co = vec3_sub(r->pt, obj->pt);
	arg[2] = vec3_dot(r->dir, obj->n) * vec3_dot(r->dir, obj->n)
		- cos(rada) * cos(rada);
	arg[1] = 2 * (vec3_dot(r->dir, obj->n) * vec3_dot(co, obj->n)
			- vec3_dot(r->dir, co) * cos(rada) * cos(rada));
	arg[0] = vec3_dot(co, obj->n) * vec3_dot(co, obj->n) - vec3_dot(co, co)
		* cos(rada) * cos(rada);
}

double	get_t_caps(t_ray *ray, t_obj *obj)
{
	double	denom;
	double	t;
	t_vec3	hit_p;
	t_vec3	diff;
	t_vec3	base_center;

	base_center = vec3_add(obj->pt, vec3_scalmult(obj->scal2, obj->n));
	denom = vec3_dot(ray->dir, obj->n);
	if (fabs(denom) > EPSILON)
	{
		t = vec3_dot(vec3_sub(base_center, ray->pt), obj->n) / denom;
		if (t < EPSILON)
			return (INFINITY);
		hit_p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
		diff = vec3_sub(hit_p, base_center);
		if (vec3_norm(diff) <= (obj->scal2 * tan(obj->scal * M_PI / 180.0)))
			return (t);
	}
	return (INFINITY);
}

void	get_cone_sides(double rac[2], t_ray *ray, t_obj *obj, double *t_side)
{
	t_vec3	hit_p;
	double	cand;
	double	h;

	cand = INFINITY;
	if (rac[0] > EPSILON && rac[1] > EPSILON)
		cand = fmin(rac[0], rac[1]);
	else if (rac[0] > EPSILON)
		cand = rac[0];
	else if (rac[1] > EPSILON)
		cand = rac[1];
	if (cand != INFINITY)
	{
		hit_p = vec3_add(ray->pt, vec3_scalmult(cand, ray->dir));
		h = vec3_dot(vec3_sub(hit_p, obj->pt), obj->n);
		if (h >= 0 && h <= obj->scal2)
			*t_side = cand;
	}
}

double	hit_cone(t_ray *ray, t_obj *obj)
{
	double	args[3];
	int		ret;
	double	rac[2];
	double	t_caps;
	double	t_side;

	t_side = INFINITY;
	t_caps = INFINITY;
	if (obj->scal <= 0 || obj->scal >= 90)
		return (INFINITY);
	compute_coefs_cone(ray, obj, args);
	ret = solve_quadratic(args, rac);
	if (ret)
		get_cone_sides(rac, ray, obj, &t_side);
	if (obj->scal2 != 0)
		t_caps = get_t_caps(ray, obj);
	return (fmin(t_side, t_caps));
}
