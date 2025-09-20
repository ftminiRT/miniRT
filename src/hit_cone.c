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

// void compute_coefs_cone(t_ray *r, t_obj *obj, double *arg)
// {
// 	t_vec3	tmp;

// 	tmp = vec3_sub(r->pt, obj->pt);

// 	double dot_nv = vec3_dot(obj->n, tmp);
// 	double dot_nd = vec3_dot(obj->n, r->dir);

// 	arg[2] = vec3_dot(tmp, tmp) - (1 + obj->k) * dot_nv * dot_nv;
// 	arg[1] = 2.0 * (vec3_dot(tmp, r->dir) - (1 + obj->k) * dot_nv * dot_nd);
// 	arg[0] = vec3_dot(r->dir, r->dir) - (1 + obj->k) * dot_nd * dot_nd;
// }

void	compute_coefs_cone(t_ray *r, t_obj *obj, double *arg)
{
	t_vec3	co;
    double  rada;

    rada = obj->scal * M_PI / 180;
	co = vec3_sub(r->pt, obj->pt);
	arg[2] = vec3_dot(r->dir, obj->n) * vec3_dot(r->dir, obj->n)
		- cos(rada) * cos(rada);
	arg[1] = 2 * (vec3_dot(r->dir, obj->n) * vec3_dot(co, obj->n)
			- vec3_dot(r->dir, co) * cos(rada) * cos(rada));
	arg[0] = vec3_dot(co, obj->n) * vec3_dot(co, obj->n) - vec3_dot(co, co)
		* cos(rada) * cos(rada);
}

// 	// === INTERSECTION CAPS ===
// 	denom = vec3_dot(ray->dir, obj->n);
// 	if (fabs(denom) > EPSILON)
// 	{
// 		// Cap bas
// 		cap_center = vec3_add(obj->pt, vec3_scalmult(-obj->scal2 / 2, obj->n));
// 		t = vec3_dot(vec3_sub(cap_center, ray->pt), obj->n) / denom;
// 		if (t > EPSILON)
// 		{
// 			hit_point = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
// 			radial = vec3_sub(hit_point, cap_center);
// 			radial = vec3_sub(radial, vec3_scalmult(vec3_dot(radial, obj->n),
// 						obj->n));
// 			r_cap = (obj->scal2 / 2) * tan(angle);
// 			// rayon à cette hauteur
// 			if (vec3_norm(radial) <= r_cap && t < t_cap)
// 				t_cap = t;
// 		}
// 		// Cap haut
// 		cap_center = vec3_add(obj->pt, vec3_scalmult(obj->scal2 / 2, obj->n));
// 		t = vec3_dot(vec3_sub(cap_center, ray->pt), obj->n) / denom;
// 		if (t > EPSILON)
// 		{
// 			hit_point = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
// 			radial = vec3_sub(hit_point, cap_center);
// 			radial = vec3_sub(radial, vec3_scalmult(vec3_dot(radial, obj->n),
// 						obj->n));
// 			r_cap = (obj->scal2 / 2) * tan(angle);
// 			// rayon à cette hauteur
// 			if (vec3_norm(radial) <= r_cap && t < t_cap)
// 				t_cap = t;
// 		}
// 	}
// 	return (fmin(t_side, t_cap));
// }

double  get_t_caps(t_ray *ray, t_obj *obj)
{
    double  denom;
    double  t;
    t_vec3  hit_p;
    t_vec3  diff;
    t_vec3  base_center;
    double  base_radius;

    // calcule le centre et le rayon de la base
    base_center = vec3_add(obj->pt, vec3_scalmult(obj->scal2, obj->n));
    base_radius = obj->scal2 * tan(obj->scal * M_PI / 180.0);

    denom = vec3_dot(ray->dir, obj->n);
    if (fabs(denom) > EPSILON)
    {
        t = vec3_dot(vec3_sub(base_center, ray->pt), obj->n) / denom;
        if (t < EPSILON)
            return (INFINITY);

        // point d’intersection
        hit_p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));

        // vérifier si l’intersection tombe bien dans le disque
        diff = vec3_sub(hit_p, base_center);
        if (vec3_norm(diff) <= base_radius)
            return (t);
    }
    return (INFINITY);
}

double      hit_cone(t_ray *ray, t_obj *obj)
{
    double  args[3];
    int     ret;
    double  rac[2];
    double  t_side;
    double  t_caps;

    t_side = INFINITY;
    t_caps = INFINITY;
    if (obj->scal <= 0 || obj->scal >= 90)
        return (INFINITY);
    compute_coefs_cone(ray, obj, args);
    ret = solve_quadratic(args, rac);
    if (ret)
    {
        double cand = INFINITY;

        if (rac[0] > EPSILON && rac[1] > EPSILON)
            cand = fmin(rac[0], rac[1]);
        else if (rac[0] > EPSILON)
            cand = rac[0];
        else if (rac[1] > EPSILON)
            cand = rac[1];

        if (cand != INFINITY)
        {
            t_vec3 hit_p = vec3_add(ray->pt, vec3_scalmult(cand, ray->dir));

            // distance projetée le long de l’axe du cône
            double h = vec3_dot(vec3_sub(hit_p, obj->pt), obj->n);

            // garder seulement si entre sommet et base
            if (h >= 0 && h <= obj->scal2)
                t_side = cand;
        }
    }
    if (obj->scal2 != 0)
        t_caps = get_t_caps(ray, obj);
    return (fmin(t_side, t_caps));
}

// double	hit_cone(t_ray *ray, t_obj *obj)
// {
// 	double	dist[2];
// 	double	args[3];
// 	int		ret;
// 	double	t_side;
// 	double	t_cap;
// 	double	angle;
// 	t_vec3	hit_point;
// 	double	h;
// 	double	denom;
// 	t_vec3	cap_center;
// 	double	t;
// 	t_vec3	radial;
// 	double	r_cap;

// 	t_side = INFINITY;
// 	t_cap = INFINITY;
// 	angle = obj->scal * M_PI / 180.0;
// 	// === INTERSECTION CÔTÉ ===
// 	compute_coefs_cone(ray, obj, args);
// 	if (obj->scal <= 0 || obj->scal >= 90)
// 		return (INFINITY);
// 	ret = solve_quadratic(args, dist);
// 	if (ret)
// 	{
// 		for (int i = 0; i < 2; i++)
// 		{
// 			if (dist[i] > EPSILON)
// 			{
// 				hit_point = vec3_add(ray->pt, vec3_scalmult(dist[i], ray->dir));
// 				h = vec3_dot(vec3_sub(hit_point, obj->pt), obj->n);
// 				if (h >= -obj->scal2 / 2 && h <= obj->scal2 / 2
// 					&& dist[i] < t_side)
// 					t_side = dist[i];
// 			}
// 		}
// 	}
