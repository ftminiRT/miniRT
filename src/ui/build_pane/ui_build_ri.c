/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_ri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:21:12 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 14:59:54 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	build_ring_btns(void *rt, t_uipane *current, t_obj *o)
{
	(void)rt;
	if (add_btn(setb((t_btn_data){&o->scal, -STEP_RAY, VEC0, UIT_SCL_BTN},
				pt(106, 362), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->scal2, -STEP_BIGRAY, VEC0,
				UIT_SCL_BTN}, pt(106, 392), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->scal3, -STEP_RING, VEC0, UIT_SCL_BTN},
				pt(106, 392), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->scal, STEP_RAY, VEC0, UIT_SCL_BTN},
				pt(136, 362), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->scal2, STEP_BIGRAY, VEC0, UIT_SCL_BTN},
				pt(136, 392), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->scal3, STEP_RING, VEC0, UIT_SCL_BTN},
				pt(136, 392), BTNSZ), current))
		return (1);
	return (0);
}

int	build_pane_ri(void *rt, t_uipane *current)
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
	if (build_pane_mat(rt, current, 452))
		return (1);
	if (build_ring_btns(rt, current, o))
		return (1);
	return (0);
}
