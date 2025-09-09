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

int build_pane_dft(void *rt, t_uipane *current)
{
	t_cam	*c;
	t_light	*a;
	t_basis b;

	build_local_basis(rt, &b);
	current->cam->local_basis = b;
	c = current->cam;
	a = current->light;
	if (add_btn(setb((t_btn_data){&a->color.r, -STEP_COL, VEC0, UIT_SCL_BTN}, pt(106, 92), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&a->color.g, -STEP_COL, VEC0, UIT_SCL_BTN}, pt(106, 122), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&a->color.b, -STEP_COL, VEC0, UIT_SCL_BTN}, pt(106, 152), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&a->brightness, -STEP_BRI, VEC0, UIT_SCL_BTN}, pt(106, 182), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->pos, 0, vec3_scalmult(-STEP_POS, b.w), UIT_MV_BTN}, pt(106, 242), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->pos, 0, vec3_scalmult(-STEP_POS, b.v), UIT_MV_BTN}, pt(106, 272), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->pos, 0, vec3_scalmult(-STEP_POS, b.u), UIT_MV_BTN}, pt(106, 302), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){0,0,-STEP_CAMROT}, UIT_ROT_BTN}, pt(106, 332), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){0,-STEP_CAMROT,0}, UIT_ROT_BTN}, pt(106, 362), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){-STEP_CAMROT,0,0}, UIT_ROT_BTN}, pt(106, 392), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->fov, -STEP_FOV, VEC0, UIT_FOV_BTN}, pt(106, 422), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&a->color.r, STEP_COL, VEC0, UIT_SCL_BTN}, pt(136, 92), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&a->color.g, STEP_COL, VEC0, UIT_SCL_BTN}, pt(136, 122), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&a->color.b, STEP_COL, VEC0, UIT_SCL_BTN}, pt(136, 152), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&a->brightness, STEP_BRI, VEC0, UIT_SCL_BTN}, pt(136, 182), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->pos, 0, vec3_scalmult(STEP_POS, b.w), UIT_MV_BTN}, pt(136, 242), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->pos, 0, vec3_scalmult(STEP_POS, b.v), UIT_MV_BTN}, pt(136, 272), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->pos, 0, vec3_scalmult(STEP_POS, b.u), UIT_MV_BTN}, pt(136, 302), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){0,0,STEP_CAMROT}, UIT_ROT_BTN}, pt(136, 332), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){0,STEP_CAMROT,0}, UIT_ROT_BTN}, pt(136, 362), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->dir, 0, (t_vec3){STEP_CAMROT,0,0}, UIT_ROT_BTN}, pt(136, 392), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&c->fov, STEP_FOV, VEC0, UIT_FOV_BTN}, pt(136, 422), BTNSZ), current))
		return (1);
	return (0);
}
