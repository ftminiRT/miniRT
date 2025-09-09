/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_sp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 15:19:25 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-04 15:19:25 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_sp(void *rt, t_uipane *current)
{
	t_obj	*o;
	t_basis	b;

	o = current->obj;
	build_local_basis(rt, &o->local_basis);
	b = o->local_basis;
	if (build_pane_color(rt, current))
		return (1);
	if (build_pane_pos(rt, current, &o->pt, 182))
		return (1);
	if (build_pane_mat(rt, current, 302))
		return (1);
	if (add_btn(setb((t_btn_data){&o->scal, -STEP_RAY, VEC0, UIT_SCL_BTN},
				pt(106, 272), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->scal, STEP_RAY, VEC0, UIT_SCL_BTN},
				pt(136, 272), BTNSZ), current))
		return (1);
	return (0);
}
