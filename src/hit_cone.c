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
	t_vec3	tmp;

	tmp = vec3_sub(r->pt, obj->pt);
	arg[2] =	 /* C      */	((tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z)
				/* 1/tan^2 */	- 1 / (tan(obj->a) * tan(obj->a)))
				/* A^2     */	* ((tmp.x * obj->n.x + tmp.y * obj->n.y + tmp.z * obj->n.z) * (tmp.x * obj->n.x + tmp.y * obj->n.y + tmp.z * obj->n.z));

	arg[1] = 	/* D       */	((2 * tmp.x) + (2 * tmp.y) + (2 * tmp.z)
				/* 1/tan^2 */	- 1 / (tan(obj->a) * tan(obj->a)))
				/* AB      */	* ((tmp.x * obj->n.x + tmp.y * obj->n.y + tmp.z * obj->n.z) * ((obj->n.x * r->dir.x) + (obj->n.y * r->dir.y) + (obj->n.z * r->dir.z)));
	
	arg[0] =	/* E       */	(((r->dir.x * r->dir.x) + (r->dir.y * r->dir.y) + (r->dir.z * r->dir.z))
				/* 1/tan^2 */	- 1 / (tan(obj->a) * tan(obj->a)))
				/*  B^2    */	* (((obj->n.x * r->dir.x) + (obj->n.y * r->dir.y) + (obj->n.z * r->dir.z)) * ((obj->n.x * r->dir.x) + (obj->n.y * r->dir.y) + (obj->n.z * r->dir.z)));
}

double	hit_cone(t_ray *r, t_obj *obj)
{
	double	dist[2];
	double	args[3];
	int		ret;

	compute_coefs_cone(r, obj, args);
	if (obj->a == 0 || obj->a == 180)
		return (INFINITY);
	ret = solve_quadratic(args, dist);
	if (!ret)
		return (0);
	if (ret == 1)
		return (dist[0]);
	if (dist[0] > dist[1])
		return (dist[1]);
	return (dist[0]);
	
}