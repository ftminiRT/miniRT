/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 15:19:25 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-04 15:19:25 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	build_cam_rot(t_cam *c, t_uipane *current)
{
	if (add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){-STEP_ROT, 0, 0},
			UIT_ROT_BTN}, pt(106, 332), btn_sz()), current)
		|| add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){0, -STEP_ROT, 0},
			UIT_ROT_BTN}, pt(106, 362), btn_sz()), current)
		|| add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){STEP_ROT, 0, 0},
			UIT_ROT_BTN}, pt(136, 332), btn_sz()), current)
		|| add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){0, STEP_ROT, 0},
			UIT_ROT_BTN}, pt(136, 362), btn_sz()), current))
		return (1);
	return (0);
}

int	build_pane_dft(void *rt, t_uipane *current)
{
	t_cam	*c;
	t_basis	b;

	build_local_basis(rt, &b);
	current->cam->local_basis = b;
	c = current->cam;
	(void)b;
	if (build_pane_color(rt, current))
		return (1);
	if (add_btn(setb((t_btn_data){&current->light->brightness, -STEP_BRI,
				null_vec(), UIT_SCL_BTN}, pt(106, 182), btn_sz()), current)
			|| add_btn(setb((t_btn_data){&current->light->brightness, STEP_BRI,
				null_vec(), UIT_SCL_BTN}, pt(136, 182), btn_sz()), current))
		return (1);
	if (build_cam_rot(c, current) || build_pane_pos(rt, current, &c->pos, 242))
		return (1);
	if (add_btn(setb((t_btn_data){&c->fov, -STEP_FOV, null_vec(), UIT_FOV_BTN},
			pt(106, 392), btn_sz()), current)
		|| add_btn(setb((t_btn_data){&c->fov, STEP_FOV,
			null_vec(), UIT_FOV_BTN}, pt(136, 392), btn_sz()), current))
		return (1);
	return (0);
}
