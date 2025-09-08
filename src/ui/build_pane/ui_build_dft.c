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
	t_light	*a;
	int		step = 5;

	(void)rt;
	c = current->cam;
	a = current->light;
	if (add_btn(setb(&a->color.r, -step, pt(106, 92), BTNSZ), current) ||
		add_btn(setb(&a->color.g, -step, pt(106, 122), BTNSZ), current) ||
		add_btn(setb(&a->color.b, -step, pt(106, 152), BTNSZ), current) ||
		add_btn(setb(&a->brightness, -step, pt(106, 182), BTNSZ), current) ||
		add_btn(setb(&a->color.r, step, pt(136, 92), BTNSZ), current) ||
		add_btn(setb(&a->color.g, step, pt(136, 122), BTNSZ), current) ||
		add_btn(setb(&a->color.b, step, pt(136, 152), BTNSZ), current) ||
		add_btn(setb(&a->brightness, step, pt(136, 182), BTNSZ), current) ||
		add_btn(setb(&c->pos.x, -step, pt(106, 242), BTNSZ), current) ||
		add_btn(setb(&c->pos.y, -step, pt(106, 272), BTNSZ), current) ||
		add_btn(setb(&c->pos.z, -step, pt(106, 302), BTNSZ), current) ||
		add_btn(setb(&c->dir.x, -step, pt(106, 332), BTNSZ), current) ||
		add_btn(setb(&c->dir.y, -step, pt(106, 362), BTNSZ), current) ||
		add_btn(setb(&c->dir.z, -step, pt(106, 392), BTNSZ), current) ||
		add_btn(setb(&c->fov, -step, pt(106, 422), BTNSZ), current) ||
		add_btn(setb(&c->pos.x, step, pt(136, 242), BTNSZ), current) ||
		add_btn(setb(&c->pos.y, step, pt(136, 272), BTNSZ), current) ||
		add_btn(setb(&c->pos.z, step, pt(136, 302), BTNSZ), current) ||
		add_btn(setb(&c->dir.x, step, pt(136, 332), BTNSZ), current) ||
		add_btn(setb(&c->dir.y, step, pt(136, 362), BTNSZ), current) ||
		add_btn(setb(&c->dir.z, step, pt(136, 392), BTNSZ), current) ||
		add_btn(setb(&c->fov, step, pt(136, 422), BTNSZ), current))
		return (1);
	return (0);
}