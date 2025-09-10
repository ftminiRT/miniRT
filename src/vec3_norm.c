/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:45 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/09 18:49:36 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec3_norm(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec3_normalized(t_vec3 a)
{
	return ((t_vec3){a.x / vec3_norm(a), a.y / vec3_norm(a), a.z
		/ vec3_norm(a)});
}

double	vec3_sqnorm(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

void	vec3_normalize(t_vec3 *a)
{
	double	norm;

	norm = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	a->x = a->x / norm;
	a->y = a->y / norm;
	a->z = a->z / norm;
}
