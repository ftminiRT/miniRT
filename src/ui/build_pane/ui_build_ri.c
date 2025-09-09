/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_ri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-08 12:21:12 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-08 12:21:12 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_ri(void *rt, t_uipane *current)
{
	t_obj *o;
	t_basis	b;

	build_local_basis(rt, &b);
	o = current->obj;
	o->local_basis = b;
	if (add_btn(setb((t_btn_data){&o->color.r, -STEP_COL, VEC0, UIT_COL_BTN}, pt(106, 92), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->color.g, -STEP_COL, VEC0, UIT_COL_BTN}, pt(106, 122), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->color.b, -STEP_COL, VEC0, UIT_COL_BTN}, pt(106, 152), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->pt, 0, vec3_scalmult(-STEP_POS, b.w), UIT_MV_BTN}, pt(106, 182), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->pt, 0, vec3_scalmult(-STEP_POS, b.v), UIT_MV_BTN}, pt(106, 212), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->pt, 0, vec3_scalmult(-STEP_POS, b.u), UIT_MV_BTN}, pt(106, 242), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->n, 0, (t_vec3){-STEP_ROT,0,0}, UIT_ROT_BTN}, pt(106, 272), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->n, 0, (t_vec3){0,-STEP_ROT,0}, UIT_ROT_BTN}, pt(106, 302), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->n, 0, (t_vec3){0,0,-STEP_ROT}, UIT_ROT_BTN}, pt(106, 332), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->scal, -STEP_RAY, VEC0, UIT_SCL_BTN}, pt(106, 362), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->scal2, -STEP_BIGRAY, VEC0, UIT_SCL_BTN}, pt(106, 392), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->scal3, -STEP_RING, VEC0, UIT_SCL_BTN}, pt(106, 422), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->shine, -STEP_SH, VEC0, UIT_SCL_BTN}, pt(106, 452), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->reflect, -STEP_RF, VEC0, UIT_01_BTN}, pt(106, 492), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->color.r, STEP_COL, VEC0, UIT_COL_BTN}, pt(136, 92), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->color.g, STEP_COL, VEC0, UIT_COL_BTN}, pt(136, 122), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->color.b, STEP_COL, VEC0, UIT_COL_BTN}, pt(136, 152), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->pt, 0, vec3_scalmult(STEP_POS, b.w), UIT_MV_BTN}, pt(136, 182), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->pt, 0, vec3_scalmult(STEP_POS, b.v), UIT_MV_BTN}, pt(136, 212), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->pt, 0, vec3_scalmult(STEP_POS, b.u), UIT_MV_BTN}, pt(136, 242), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->n, 0, (t_vec3){STEP_ROT,0,0}, UIT_ROT_BTN}, pt(136, 272), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->n, 0, (t_vec3){0,STEP_ROT,0}, UIT_ROT_BTN}, pt(136, 302), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->n, 0, (t_vec3){0,0,STEP_ROT}, UIT_ROT_BTN}, pt(136, 332), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->scal, STEP_RAY, VEC0, UIT_SCL_BTN}, pt(136, 362), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->scal2, STEP_BIGRAY, VEC0, UIT_SCL_BTN}, pt(136, 392), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->scal3, STEP_RING, VEC0, UIT_SCL_BTN}, pt(136, 422), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->shine, STEP_SH, VEC0, UIT_SCL_BTN}, pt(136, 452), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&o->reflect, STEP_RF, VEC0, UIT_01_BTN}, pt(136, 482), BTNSZ), current))
		return (1);
	return (0);
}

