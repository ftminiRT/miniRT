/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_co.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:19:25 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 14:58:14 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_co(void *rt, t_uipane *current)
{
	t_obj	*o;
	t_basis	b;

	o = current->obj;
	build_local_basis(rt, &o->local_basis);
	b = o->local_basis;
	(void)b;
	if (build_pane_color(rt, current))
		return (1);
	if (build_pane_pos(rt, current, &o->pt, 182))
		return (1);
	if (build_pane_dir(rt, current, &o->n, 272))
		return (1);
	if (build_pane_mat(rt, current, 392))
		return (1);
	if (add_btn(setb((t_btn_data){&o->scal, -STEP_RAY,
				null_vec(), UIT_SCL_BTN}, pt(106, 362), btn_sz()), current)
				|| add_btn(setb((t_btn_data){&o->scal, STEP_RAY,
				null_vec(), UIT_SCL_BTN}, pt(136, 362), btn_sz()), current)
				|| add_btn(setb((t_btn_data){&o->scal2, -STEP_HEI,
				null_vec(), UIT_SCL_BTN}, pt(106, 392), btn_sz()), current)
				|| add_btn(setb((t_btn_data){&o->scal2, STEP_HEI,
				null_vec(), UIT_SCL_BTN}, pt(136, 392), btn_sz()), current);
		return (1);
	return (0);
}
