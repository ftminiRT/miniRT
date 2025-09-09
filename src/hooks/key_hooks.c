/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:57 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/09 23:10:10 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_valid_key_code(int kc, t_env *rt)
{
	if (kc == KEY_ESC)
		return (true);
	if (kc == KEY_C || kc == KEY_A || kc == KEY_S)
		return (true);
	if (kc == KEY_LEFT || kc == KEY_RIGHT || kc == KEY_UP || kc == KEY_DOWN
		|| kc == KEY_PLUS || kc == KEY_MINUS)
		return (true);
	if (kc == KEY_J || kc == KEY_L || kc == KEY_K || kc == KEY_I)
		return (true);
	if (rt->selected.type != CAM && (kc == KEY_U || kc == KEY_O))
		return (true);
	if (rt->selected.type == OBJ && rt->selected.obj)
	{
		if (rt->selected.obj->type == OT_RING && (kc == KEY_Q || kc == KEY_W))
			return (true);
		if (kc == KEY_MINUS2 || kc == KEY_PLUS2 || kc == KEY_X)
			return (true);
	}
	if (kc == KEY_B)
		return (true);
	return (false);
}
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
	if (kc == KEY_E)
		export_to_rt(rt);
	if (kc == KEY_T)
	{
		rt->render = !rt->render;
		if (rt->render)
			ray_trace(rt);
	}
	if (is_valid_key_code(kc, rt))
		ray_trace(rt);
	return (1);
}

int	close_window(t_env *rt)
{
	clear_mlx(rt);
	exit(0);
	return (0);
}
