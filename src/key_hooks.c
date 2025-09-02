/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:57 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/26 15:38:48 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void move_selected(t_env *rt, t_vec3 move)
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

static void	rotate_selected(t_env *rt, t_vec3 rot)
{
	if (rt->selected.type == CAM)
		vec3_rotate(&rt->cam.dir, rot);
	else if (rt->selected.type == OBJ && rt->selected.obj)
		vec3_rotate(&rt->selected.obj->n, rot);
}

int	key_pressed(int kc, t_env *rt)
{
	double	step = 5;
	t_vec3	fwd = vec3_normalized(rt->cam.dir);
	t_vec3	up = (t_vec3){0,1,0};
	t_vec3	right = vec3_normalized(vec3_cross(fwd, up));

	if (kc == KEY_ESC)
	{
		clear_mlx(rt);
		mrt_cleaner(rt);
		exit(1);
	}
	if (kc == KEY_C)
		rt->selected.type = CAM;
	if (kc == KEY_S)
	{
		rt->selected.type = SPOT;
		if (rt->selected.spot->next)
			rt->selected.spot = rt->selected.spot->next;
		else
			rt->selected.spot = &rt->spot;
	}
	if (kc == KEY_A)
		rt->selected.type = AMB;
	if (kc == KEY_LEFT)
		move_selected(rt, vec3_scalmult(-step, right));
	if (kc == KEY_RIGHT)
		move_selected(rt, vec3_scalmult(step, right));
	if (kc == KEY_UP)
		move_selected(rt, vec3_scalmult(step, up));
	if (kc == KEY_DOWN)
		move_selected(rt, vec3_scalmult(-step, up));
	if (kc == KEY_PLUS)
		move_selected(rt, vec3_scalmult(step, fwd));
	if (kc == KEY_MINUS)
		move_selected(rt, vec3_scalmult(-step, fwd));
	if (kc == KEY_J)
		rotate_selected(rt, (t_vec3){0, -step, 0});
	if (kc == KEY_L)
		rotate_selected(rt, (t_vec3){0, step, 0});
	if (kc == KEY_K)
		rotate_selected(rt, (t_vec3){-step, 0, 0});
	if (kc == KEY_I)
		rotate_selected(rt, (t_vec3){step, 0, 0});
	if (kc == KEY_U)
		rotate_selected(rt, (t_vec3){0, 0, -step});
	if (kc == KEY_O)
		rotate_selected(rt, (t_vec3){0, 0, step});
	if (rt->selected.type == OBJ && kc == KEY_X)
		rt->selected.obj->checkered = !rt->selected.obj->checkered;
	ray_trace(rt);
	return (1);
}

int	close_window(t_env *rt)
{
	clear_mlx(rt);
	exit(0);
	return (0);
}
