/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 16:12:04 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 16:12:04 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_events(void *rt, t_uipane *current)
{
	t_cam	*c;
	t_light	*s;

	(void)rt;
	(void)current;
	c = current->cam;
	s = current->light;
	if (add_btn(setb((t_btn_data){&c, 1, null_vec(), UIT_SPOT_BTN}, pt(55, 17),
			btn_sz()), current) || add_btn(setb((t_btn_data){&s, 1, null_vec(),
			UIT_CAM_BTN}, pt(85, 17), btn_sz()), current)
		|| add_btn(setb((t_btn_data){NULL, 1, null_vec(), UIT_EXPORT_BTN},
		pt(115, 17), btn_sz()), current) || add_btn(setb((t_btn_data){NULL, 1,
			null_vec(), UIT_RND_BTN}, pt(145, 17), btn_sz()), current))
		return (1);
	return (0);
}
