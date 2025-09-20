/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 16:02:09 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 16:02:09 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_value_buttons(t_env *rt, t_items *itm)
{
	double			*val;
	unsigned char	*u8val;

	(void)rt;
	if (itm->type == UIT_SCL_BTN)
	{
		val = (double *)itm->btn.value;
		*val = fmax(0, *val + itm->btn.factor);
	}
	else if (itm->type == UIT_01_BTN)
	{
		val = (double *)itm->btn.value;
		*val = fmin(1, fmax(0, *val + itm->btn.factor));
	}
	else if (itm->type == UIT_COL_BTN)
	{
		u8val = (unsigned char *)itm->btn.value;
		*u8val = (unsigned char)fmin(255, fmax(0, *u8val + itm->btn.factor));
	}
	else if (itm->type == UIT_FOV_BTN)
	{
		u8val = (unsigned char *)itm->btn.value;
		*u8val = (unsigned char)fmin(170, fmax(0, *u8val + itm->btn.factor));
	}
}

static void	handle_vector_buttons(t_env *rt, t_items *itm)
{
	double	*value;

	(void)rt;
	if (itm->type == UIT_SH_BTN)
	{
		value = (double *)itm->btn.value;
		*value = fmax(1, *value * itm->btn.factor);
	}
	else if (itm->type == UIT_MV_BTN)
		move_vec3((t_vec3 *)itm->btn.value, itm->btn.v);
	else if (itm->type == UIT_ROT_BTN)
		vec3_rotate((t_vec3 *)itm->btn.value, itm->btn.v);
}

static void	handle_selection_buttons(t_env *rt, t_items *itm)
{
	if (itm->type == UIT_SEL_BTN && itm->btn.factor == -1)
		rt->ui.current = get_prev_spot(rt);
	else if (itm->type == UIT_SEL_BTN && itm->btn.factor == 1)
		rt->ui.current = get_next_spot(rt);
	else if (itm->type == UIT_SPOT_BTN)
		rt->ui.current = get_spot(rt);
	else if (itm->type == UIT_CAM_BTN)
		rt->ui.current = get_default_pane_addr(rt);
}

void	exec_button(t_env *rt, t_items *itm)
{
	if (!itm)
		return ;
	handle_value_buttons(rt, itm);
	handle_vector_buttons(rt, itm);
	handle_selection_buttons(rt, itm);
	if (itm->type == UIT_EXPORT_BTN)
	{
		printf("Exporting set...\n");
		export_to_rt(rt);
	}
	else if (itm->type == UIT_RND_BTN)
		rt->render = !rt->render;
	else if (itm->function)
		itm->function(rt);
}
