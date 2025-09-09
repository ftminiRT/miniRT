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

int	build_pane_dft(void *rt, t_uipane *current)
{
	t_cam	*c;
	t_basis	b;

	build_local_basis(rt, &b);
	current->cam->local_basis = b;
	c = current->cam;
	if (build_pane_color(rt, current))
		return (1);
	if (add_btn(setb((t_btn_data){&current->light->brightness, -STEP_BRI, VEC0,
				UIT_SCL_BTN}, pt(106, 182), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&current->light->brightness, STEP_BRI,
				VEC0, UIT_SCL_BTN}, pt(136, 182), BTNSZ), current))
		return (1);
	if (build_pane_pos(rt, current, &c->pos, 242))
		return (1);
	if (build_pane_dir(rt, current, &c->dir, 332))
		return (1);
	if (add_btn(setb((t_btn_data){&c->fov, -STEP_FOV, VEC0, UIT_FOV_BTN},
			pt(106, 392), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&c->fov, STEP_FOV, VEC0, UIT_FOV_BTN},
			pt(136, 392), BTNSZ), current))
		return (1);
	return (0);
}
