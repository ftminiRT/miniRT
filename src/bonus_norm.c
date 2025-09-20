/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:27:12 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:27:12 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	cone_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3	tmp;
	t_vec3	ret;
	double	angle;
	double	k;

	angle = (obj->scal * M_PI) / 180.0;
	k = 1.0 + (tan(angle) * tan(angle));
	tmp = vec3_sub(hit_point, obj->pt);
	ret.x = 2 * tmp.x;
	ret.y = 2 * tmp.y;
	ret.z = 2 * (tmp.z) - 2 * k * vec3_dot(tmp, obj->n) * obj->n.z;
	vec3_normalize(&ret);
	return (ret);
}
