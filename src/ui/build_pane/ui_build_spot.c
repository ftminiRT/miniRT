/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_spot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 15:19:25 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-04 15:19:25 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_spot(void *rt, t_uipane *current)
{
	t_light	*s;
	t_basis b;

	s = current->light;
	build_local_basis(rt, &s->local_basis);
	b = s->local_basis;
	if (add_btn(setb((t_btn_data){&s->color.r, -STEP_COL, VEC0, UIT_SCL_BTN}, pt(106, 92), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->color.g, -STEP_COL, VEC0, UIT_SCL_BTN}, pt(106, 122), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->color.b, -STEP_COL, VEC0, UIT_SCL_BTN}, pt(106, 152), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->pos, 0, vec3_scalmult(-STEP_SPOS, b.w), UIT_MV_BTN}, pt(106, 182), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->pos, 0, vec3_scalmult(-STEP_SPOS, b.v), UIT_MV_BTN}, pt(106, 212), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->pos, 0, vec3_scalmult(-STEP_SPOS, b.u), UIT_MV_BTN}, pt(106, 242), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->brightness, -STEP_BRI, VEC0, UIT_SCL_BTN}, pt(106, 272), BTNSZ), current) ||
		add_btn(setb((t_btn_data){0, -1, VEC0, UIT_SEL_BTN}, pt(106, 302), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->color.r, STEP_COL, VEC0, UIT_SCL_BTN}, pt(136, 92), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->color.g, STEP_COL, VEC0, UIT_SCL_BTN}, pt(136, 122), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->color.b, STEP_COL, VEC0, UIT_SCL_BTN}, pt(136, 152), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->pos, 0, vec3_scalmult(STEP_SPOS, b.w), UIT_MV_BTN}, pt(136, 182), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->pos, 0, vec3_scalmult(STEP_SPOS, b.v), UIT_MV_BTN}, pt(136, 212), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->pos, 0, vec3_scalmult(STEP_SPOS, b.u), UIT_MV_BTN}, pt(136, 242), BTNSZ), current) ||
		add_btn(setb((t_btn_data){&s->brightness, STEP_BRI, VEC0, UIT_SCL_BTN}, pt(136, 272), BTNSZ), current) ||
		add_btn(setb((t_btn_data){0, 1, VEC0, UIT_SEL_BTN}, pt(136, 302), BTNSZ), current))
		return (1);
	return (0);
}