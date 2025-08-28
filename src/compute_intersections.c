/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_intersections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:12:07 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 14:12:56 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*compute_intersections(t_env *rt, t_ray *ray)
{
	t_obj	*objs;
	double	closest_t;
	double	t;
	t_obj	*closest;

	closest_t = INFINITY;
	t = INFINITY;
	closest = NULL;
	objs = rt->objects;
	while (objs)
	{
		t = rt->hit_object[objs->type](ray, objs);
		if (0 < t && t < closest_t)
		{
			closest_t = t;
			closest = objs;
		}
		objs = objs->next;
	}
	if (closest)
		ray->hit = closest_t;
	return (closest);
}
