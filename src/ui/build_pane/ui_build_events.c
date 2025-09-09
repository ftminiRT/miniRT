/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:25:33 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 13:25:34 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_events(void *rt, t_uipane *current)
{
	t_cam *c;
	t_light *s;

	(void)rt;
	(void)current;
	c = current->cam;
	s = current->light;
	if (add_btn(setb((t_btn_data){&c, 1, VEC0, UIT_SPOT_BTN}, pt(55, 17),
				BTNSZ), current) || add_btn(setb((t_btn_data){&s, 1, VEC0,
				UIT_CAM_BTN}, pt(85, 17), BTNSZ), current)
		|| add_btn(setb((t_btn_data){NULL, 1, VEC0, UIT_EXPORT_BTN}, pt(115,
					17), BTNSZ), current) || add_btn(setb((t_btn_data){NULL, 1,
				VEC0, UIT_RND_BTN}, pt(135, 17), BTNSZ), current))
		return (1);
	return (0);
}