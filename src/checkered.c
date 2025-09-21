/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkered.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:52:22 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/21 00:35:09 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_clamp(double x, int min, int max)
{
	if (x > max)
		x = max;
	if (x < min)
		x = min;
	return (x);
}

t_color	get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	int	map[2];
	int	checker;

	(void)rt;
	rt->get_uv[obj->type](obj, hit_point, map);
	// if (obj->type == OT_PLANE)
	// 	get_plane_uv(obj, hit_point, map);
	// else if (obj->type == OT_SPHERE)
	// 	get_sphere_uv(obj, hit_point, map);
	// else if (obj->type == OT_CYL)
	// 	get_cylinder_uv(obj, hit_point, map);
	// else if (obj->type == OT_TORE)
	// 	get_torus_uv(obj, hit_point, map);
	// else if (obj->type == OT_MOEB)
	// 	get_moebius_uv(obj, hit_point, map);
	// else if (obj->type == OT_RING)
	// 	get_ring_uv(obj, hit_point, map);
	// else
	// 	return (obj->color);
	checker = (map[0] + map[1]) % 2;
	if (checker == 0)
		return (obj->color);
	return ((t_color){0, 0, 0});
}
