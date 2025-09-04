/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:57 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/03 07:41:04 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_selected(t_env *rt, t_vec3 move)
{
	if (rt->selected.type == CAM)
		rt->cam.pos = vec3_add(rt->cam.pos, move);
	else if (rt->selected.type == SPOT && rt->selected.spot)
		rt->selected.spot->pos = vec3_add(rt->selected.spot->pos, move);
	else if (rt->selected.type == AMB && rt->selected.amb)
		rt->selected.amb->pos = vec3_add(rt->selected.amb->pos, move);
	else if (rt->selected.type == OBJ && rt->selected.obj)
		rt->selected.obj->pt = vec3_add(rt->selected.obj->pt, move);
}

void	rotate_selected(t_env *rt, t_vec3 rot)
{
	if (rt->selected.type == CAM)
		vec3_rotate(&rt->cam.dir, rot);
	else if (rt->selected.type == OBJ && rt->selected.obj)
		vec3_rotate(&rt->selected.obj->n, rot);
}

int	key_pressed(int kc, t_env *rt)
{
	double	step;
	t_vec3	fwd;

	handle_exit(kc, rt);
	handle_selection(kc, rt);
	step = 5;
	fwd = vec3_normalized(rt->cam.dir);
	handle_movement(kc, rt, step, fwd);
	handle_rotation(kc, rt, step);
	handle_object_mod(kc, rt, step);
	ray_trace(rt);
	return (1);
}

int	close_window(t_env *rt)
{
	clear_mlx(rt);
	exit(0);
	return (0);
}
