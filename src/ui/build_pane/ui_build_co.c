/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_co.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 15:19:25 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-04 15:19:25 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_co(void *rt, t_uipane *current)
{
	double step = 1;
	t_obj *o;

	(void)rt;
	o = current->obj;
	if (add_btn(setb(&o->color.r, -step, pt(106, 92), BTNSZ), current) ||
		add_btn(setb(&o->color.g, -step, pt(106, 122), BTNSZ), current) ||
		add_btn(setb(&o->color.b, -step, pt(106, 152), BTNSZ), current) ||
		add_btn(setb(&o->pt.x, -step, pt(106, 182), BTNSZ), current) ||
		add_btn(setb(&o->pt.y, -step, pt(106, 212), BTNSZ), current) ||
		add_btn(setb(&o->pt.z, -step, pt(106, 242), BTNSZ), current) ||
		add_btn(setb(&o->n.x, -step, pt(106, 272), BTNSZ), current) ||
		add_btn(setb(&o->n.y, -step, pt(106, 302), BTNSZ), current) ||
		add_btn(setb(&o->n.z, -step, pt(106, 332), BTNSZ), current) ||
		add_btn(setb(&o->scal, -step, pt(106, 362), BTNSZ), current) ||
		add_btn(setb(&o->shine, -STEP_SH, pt(106, 392), BTNSZ), current) ||
		// add_btn(setb(&o->reflect, -STEP_RF, pt(106, 422}, BTNSZ), current) ||
		add_btn(setb(&o->color.r, step, pt(136, 92), BTNSZ), current) ||
		add_btn(setb(&o->color.g, +step, pt(136, 122), BTNSZ), current) ||
		add_btn(setb(&o->color.b, step, pt(136, 152), BTNSZ), current) ||
		add_btn(setb(&o->pt.x, step, pt(136, 182), BTNSZ), current) ||
		add_btn(setb(&o->pt.y, step, pt(136, 212), BTNSZ), current) ||
		add_btn(setb(&o->pt.z, step, pt(136, 242), BTNSZ), current) ||
		add_btn(setb(&o->n.x, step, pt(136, 272), BTNSZ), current) ||
		add_btn(setb(&o->n.y, step, pt(136, 302), BTNSZ), current) ||
		add_btn(setb(&o->n.z, step, pt(136, 332), BTNSZ), current) ||
		add_btn(setb(&o->scal, step, pt(136, 362), BTNSZ), current) ||
		add_btn(setb(&o->shine, STEP_SH, pt(136, 392), BTNSZ), current))// ||
		// add_btn(setb(&o->reflect, STEP_RF, pt(136, 422}, BTNSZ), current))
		return (1);
	return (0);
}