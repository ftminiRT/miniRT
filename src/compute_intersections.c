/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_intersections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:12:07 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 18:55:15 by tbeauman         ###   ########.fr       */
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
		printf("%d %s\n",__LINE__,__FILE__);
		fflush(stdout);
		printf("%d\n", objs->type);
		fflush(stdout);
		printf("%p\n", rt->hit_object[objs->type]);
		if (rt->hit_object[objs->type] == NULL)
			printf("NULL MANDANDA\n");
		fflush(stdout);
		t = rt->hit_object[objs->type](ray, objs);
		printf("%d %s\n",__LINE__,__FILE__);
		fflush(stdout);
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
