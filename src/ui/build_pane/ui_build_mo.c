/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_mo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:19:25 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 15:05:05 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_mo(void *rt, t_uipane *current)
{
	t_obj	*o;
	t_basis	b;

	build_local_basis(rt, &b);
	o = current->obj;
	o->local_basis = b;
	if (build_pane_color(rt, current))
		return (1);
	if (build_pane_pos(rt, current, &o->pt, 182))
		return (1);
	if (build_pane_dir(rt, current, &o->n, 272))
		return (1);
	if (build_pane_mat(rt, current, 392))
		return (1);
	if (add_btn(setb((t_btn_data){&o->scal, -STEP_RAY, VEC0, UIT_SCL_BTN},
				pt(106, 332), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->max, -STEP_MAX, VEC0, UIT_SCL_BTN},
				pt(106, 362), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->scal, STEP_RAY, VEC0, UIT_SCL_BTN},
				pt(136, 332), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->max, STEP_MAX, VEC0, UIT_SCL_BTN},
				pt(136, 362), BTNSZ), current))
		return (1);
	return (0);
}
