/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cyl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:17:17 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 14:23:35 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_proj_data	calc_projections(t_ray *ray, t_obj *cy, t_vec3 oc)
{
	t_proj_data	proj;
	double		d_dot_n;
	double		oc_dot_n;

	d_dot_n = vec3_dot(ray->dir, cy->n);
	oc_dot_n = vec3_dot(oc, cy->n);
	proj.d_proj = vec3_sub(ray->dir, vec3_scalmult(d_dot_n, cy->n));
	proj.oc_proj = vec3_sub(oc, vec3_scalmult(oc_dot_n, cy->n));
	proj.a = vec3_dot(proj.d_proj, proj.d_proj);
	proj.b = 2.0 * vec3_dot(proj.d_proj, proj.oc_proj);
	proj.c = vec3_dot(proj.oc_proj, proj.oc_proj) - cy->scal * cy->scal;
	return (proj);
}

static bool	is_valid_cylinder_hit(t_ray *ray, t_obj *cy, double t)
{
	t_vec3	p;
	t_vec3	from_center;
	double	h;

	if (t < EPSILON)
		return (false);
	p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
	from_center = vec3_sub(p, cy->pt);
	h = vec3_dot(from_center, cy->n);
	return (fabs(h) <= cy->scal2 / 2.0);
}

static double	hit_cylinder_body(t_ray *ray, t_obj *cy, t_vec3 oc)
{
	t_proj_data	proj;
	double		t1;
	double		t2;
	double		t_hit;

	proj = calc_projections(ray, cy, oc);
	proj.delta = proj.b * proj.b - 4 * proj.a * proj.c;
	if (proj.delta < 0)
		return (INFINITY);
	proj.sqrt_d = sqrt(proj.delta);
	t1 = (-proj.b - proj.sqrt_d) / (2.0 * proj.a);
	t2 = (-proj.b + proj.sqrt_d) / (2.0 * proj.a);
	t_hit = INFINITY;
	if (is_valid_cylinder_hit(ray, cy, t1) && t1 < t_hit)
		t_hit = t1;
	if (is_valid_cylinder_hit(ray, cy, t2) && t2 < t_hit)
		t_hit = t2;
	return (t_hit);
}

static double	hit_cylinder_cap(t_ray *ray, t_obj *cy, int cap_index)
{
	t_vec3	center;
	double	delta;
	double	t;
	t_vec3	p;

	if (cap_index == 0)
		center = vec3_add(cy->pt, vec3_scalmult(-cy->scal2 / 2.0, cy->n));
	else
		center = vec3_add(cy->pt, vec3_scalmult(cy->scal2 / 2.0, cy->n));
	delta = vec3_dot(ray->dir, cy->n);
	if (fabs(delta) < EPSILON)
		return (INFINITY);
	t = vec3_dot(vec3_sub(center, ray->pt), cy->n) / delta;
	if (t < EPSILON)
		return (INFINITY);
	p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
	if (vec3_norm(vec3_sub(p, center)) <= cy->scal)
		return (t);
	return (INFINITY);
}

double	hit_cylinder(t_ray *ray, t_obj *cy)
{
	t_vec3	oc;
	double	t_body;
	double	t_cap1;
	double	t_cap2;
	double	t_hit;

	oc = vec3_sub(ray->pt, cy->pt);
	t_body = hit_cylinder_body(ray, cy, oc);
	t_cap1 = hit_cylinder_cap(ray, cy, 0);
	t_cap2 = hit_cylinder_cap(ray, cy, 1);
	t_hit = t_body;
	if (t_cap1 < t_hit)
		t_hit = t_cap1;
	if (t_cap2 < t_hit)
		t_hit = t_cap2;
	return (t_hit);
}
