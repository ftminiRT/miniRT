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

// void	compute_coefs_cone(t_ray *r, t_obj *obj, double *arg)
// {
// 	t_vec3	tmp;
// 	double	angle;

// 	angle = (obj->scal * M_PI) / 180.0;
// 	tmp = vec3_sub(r->pt, obj->pt);
// 	arg[2] =	 /* C      */	vec3_dot(tmp,tmp)
// 				/* 1/tan^2 */	- (1 / (tan(angle) * tan(angle)))
// 				/* A^2     */	* vec3_dot(obj->n, tmp) * vec3_dot(obj->n, tmp);

// 	arg[1] = 	/* D       */	2 * vec3_dot(tmp, r->dir)
// 				/* 1/tan^2 */	- (1 / (tan(angle) * tan(angle)))
// 				/* AB      */	* vec3_dot(tmp, obj->n) * 
// 									vec3_dot(obj->n, r->dir);
	
// 	arg[0] =	/* E       */	vec3_dot(r->dir, r->dir)
// 				/* 1/tan^2 */	- (1 / (tan(angle) * tan(angle)))
// 				/*  B^2    */	* vec3_dot(obj->n, r->dir) * vec3_dot(obj->n, r->dir);
// }

void compute_coefs_cone(t_ray *r, t_obj *obj, double *arg)
{
	t_vec3	tmp;
	double	angle;
	double	k;

	angle = (obj->scal * M_PI) / 180.0;
	k = 1.0 / (tan(angle) * tan(angle)); // cos²θ

	tmp = vec3_sub(r->pt, obj->pt);

	double dot_nv = vec3_dot(obj->n, tmp);
	double dot_nd = vec3_dot(obj->n, r->dir);

	arg[2] = vec3_dot(tmp, tmp) - k * dot_nv * dot_nv;
	arg[1] = 2.0 * (vec3_dot(tmp, r->dir) - k * dot_nv * dot_nd);
	arg[0] = vec3_dot(r->dir, r->dir) - k * dot_nd * dot_nd;
}


double	hit_cone(t_ray *r, t_obj *obj)
{
	double	dist[2];
	double	args[3];
	int		ret;

	compute_coefs_cone(r, obj, args);
	if (obj->scal <= 0 || obj->scal >= 180)
		return (INFINITY);
	ret = solve_quadratic(args, dist);
	if (!ret)
		return (INFINITY);
	if (dist[0] > EPSILON)
		return (dist[0]);
	if (dist[1] > EPSILON)
		return (dist[1]);
	return (INFINITY);
}