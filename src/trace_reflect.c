/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_reflect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-21 09:49:49 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-21 09:49:49 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	manage_reflect(t_env *rt, t_reflect_data *d, t_ray ray, int depth)
{
	if (d->hitted->reflect > 0.0)
	{
		d->normal = rt->get_norm[d->hitted->type](d->hitted, d->hit_point);
		if (vec3_dot(ray.dir, d->normal) > 0)
			d->normal = vec3_scalmult(-1, d->normal);
		d->reflected = reflect(ray.dir, d->normal);
		d->hit_point = vec3_add(d->hit_point,
				vec3_scalmult(EPSILON, d->normal));
		d->reflected_ray = (t_ray){d->hit_point, d->reflected, 0,
			(t_color){0, 0, 0}};
		d->reflected_color = trace_ray(rt, d->reflected_ray, depth + 1);
		d->local_color.r = (1 - d->hitted->reflect) * d->local_color.r
			+ d->hitted->reflect * d->reflected_color.r;
		d->local_color.g = (1 - d->hitted->reflect) * d->local_color.g
			+ d->hitted->reflect * d->reflected_color.g;
		d->local_color.b = (1 - d->hitted->reflect) * d->local_color.b
			+ d->hitted->reflect * d->reflected_color.b;
	}
}
