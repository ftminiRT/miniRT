/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:17:01 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/27 14:56:15 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(t_ray *ray, t_obj *s)
{
	double	b;
	double	c;
	double	delta;
	double	sqrt_d;
	double	hit1;
	double	hit2;
	t_vec3	oc;

	oc = vec3_sub(ray->pt, s->pt);
	b = vec3_dot(oc, ray->dir);
	c = vec3_dot(oc, oc) - s->scal * s->scal;
	delta = b * b - c;
	if (delta < 0)
		return (INFINITY);
	sqrt_d = sqrt(delta);
	hit1 = -b - sqrt_d;
	hit2 = -b + sqrt_d;
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
/*
double	hit_cylinder(t_ray *ray, t_obj *cy)
{
	t_vec3	oc;
	double	d_dot_n;
	double	oc_dot_n;
	t_vec3	d_proj;
	t_vec3	oc_proj;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sqrt_d;
	double	t1;
	double	t2;
	double	t;
	t_vec3	p;
	t_vec3	from_center;
	double	h;

	oc = vec3_sub(ray->pt, cy->pt);
	d_dot_n = vec3_dot(ray->dir, cy->n);
	oc_dot_n = vec3_dot(oc, cy->n);
	d_proj = vec3_sub(ray->dir, vec3_scalmult(d_dot_n, cy->n));
	oc_proj = vec3_sub(oc, vec3_scalmult(oc_dot_n, cy->n));
	a = vec3_dot(d_proj, d_proj);
	b = 2 * vec3_dot(d_proj, oc_proj);
	c = vec3_dot(oc_proj, oc_proj) - cy->scal * cy->scal;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (INFINITY);
	if (delta >= 0)
	{
		sqrt_d = sqrt(delta);
		t1 = (-b - sqrt_d) / (2 * a);
		t2 = (-b + sqrt_d) / (2 * a);
		for (int i = 0; i < 2; i++)
		{
			t = (i == 0) ? t1 : t2;
			if (t < EPSILON)
				continue ;
			p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
			from_center = vec3_sub(p, cy->pt);
			h = vec3_dot(from_center, cy->n);
			if (fabs(h) <= cy->scal2 / 2.0)
				return (t);
		}
	}
	// --- Intersections avec les deux disques de fermeture ---
	for (int i = 0; i < 2; i++)
	{
		t_vec3 center = vec3_add(cy->pt, vec3_scalmult((i == 0 ? -1 : 1) * cy->scal2 / 2.0, cy->n));
		double denom = vec3_dot(ray->dir, cy->n);
		if (fabs(denom) < EPSILON)
			continue ; // rayon parallèle au disque
		t = vec3_dot(vec3_sub(center, ray->pt), cy->n) / denom;
		if (t < EPSILON)
			continue ;
		p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
		if (vec3_norm(vec3_sub(p, center)) <= cy->scal)
			return (t);
	}

	return (INFINITY);
}
*/

double	hit_cylinder(t_ray *ray, t_obj *cy)
{
	t_vec3	oc, d_proj, oc_proj, p, from_center, center;
	double	d_dot_n, oc_dot_n;
	double	a, b, c, delta, sqrt_d;
	double	t1, t2, t;
	double	h;
	double	t_hit = INFINITY;

	// --- projection pour le cylindre infini ---
	oc = vec3_sub(ray->pt, cy->pt);
	d_dot_n = vec3_dot(ray->dir, cy->n);
	oc_dot_n = vec3_dot(oc, cy->n);
	d_proj = vec3_sub(ray->dir, vec3_scalmult(d_dot_n, cy->n));
	oc_proj = vec3_sub(oc, vec3_scalmult(oc_dot_n, cy->n));

	a = vec3_dot(d_proj, d_proj);
	b = 2.0 * vec3_dot(d_proj, oc_proj);
	c = vec3_dot(oc_proj, oc_proj) - cy->scal * cy->scal;

	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		sqrt_d = sqrt(delta);
		t1 = (-b - sqrt_d) / (2.0 * a);
		t2 = (-b + sqrt_d) / (2.0 * a);
		for (int i = 0; i < 2; i++)
		{
			t = (i == 0) ? t1 : t2;
			if (t < EPSILON)
				continue;
			p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
			from_center = vec3_sub(p, cy->pt);
			h = vec3_dot(from_center, cy->n);
			if (fabs(h) <= cy->scal2 / 2.0 && t < t_hit)
				t_hit = t;
		}
	}

	// --- intersections avec les disques de fermeture ---
	for (int i = 0; i < 2; i++)
	{
		center = vec3_add(cy->pt, vec3_scalmult((i == 0 ? -1.0 : 1.0) * cy->scal2 / 2.0, cy->n));
		double denom = vec3_dot(ray->dir, cy->n);
		if (fabs(denom) < EPSILON)
			continue; // rayon parallèle au disque
		t = vec3_dot(vec3_sub(center, ray->pt), cy->n) / denom;
		if (t < EPSILON)
			continue;
		p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
		if (vec3_norm(vec3_sub(p, center)) <= cy->scal && t < t_hit)
			t_hit = t;
	}

	return t_hit;
}
