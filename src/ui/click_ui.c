/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-02 13:51:31 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-02 13:51:31 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
void	move_vec3(t_vec3 *v, t_vec3 move)
{
	*v = vec3_add(*v, move);
}

void	rotate_vec3(t_vec3 *n, t_vec3 rot)
{
	vec3_rotate(n, rot);
}

void exec_button(t_env *rt, t_items *itm)
{
	double *val;
	unsigned char *u8val;

	if (!itm)
		return;

	if (itm->type == UIT_SCL_BTN)
	{
		val = (double*)itm->btn.value;
		*val = fmax(0, *val + itm->btn.factor);
	}
	else if (itm->type == UIT_01_BTN)
	{
		val = (double*)itm->btn.value;
		*val = fmin(1, fmax(0, *val + itm->btn.factor));
	}
	else if (itm->type == UIT_COL_BTN)
	{
		u8val = (unsigned char*)itm->btn.value;
		*u8val = (unsigned char)fmin(255, fmax(0, *u8val + itm->btn.factor));
	}
	else if (itm->type == UIT_FOV_BTN)
	{
		u8val = (unsigned char*)itm->btn.value;
		*u8val = (unsigned char)fmin(170, fmax(0, *u8val + itm->btn.factor));
	}
	else if (itm->type == UIT_MV_BTN)
		move_vec3((t_vec3*)itm->btn.value, itm->btn.v);
	else if (itm->type == UIT_ROT_BTN)
		rotate_vec3((t_vec3*)itm->btn.value, itm->btn.v);
	else if (itm->function)
		itm->function(rt);
	debug_print_set(rt);
}

int	hit_ui(int x, int y, t_items *itm)
{
	if ((x > itm->pos.x - (itm->scale.x / 2) && \
		x < itm->pos.x + (itm->scale.x / 2)) && \
		y > itm->pos.y - (itm->scale.y / 2) && \
		y < itm->pos.y + (itm->scale.y / 2))
		return (printf("button clicked at %d, %d\n", x, y), 1);
	return (0);
}

void click_ui(int x, int y, t_env *rt)
{
	int 	found;
	int		dft;
	t_items	*current;

	dft = 0;
	found = 0;
	current = rt->ui.current->itms;
	if (!current)
	{
		current = rt->ui.dft_itms;
		dft = 1;
	}
	while (current)
	{
		found = hit_ui(x, y, current);
		if (found)
			break ;
		current = current->next;
		if (!current && !dft)
		{
			dft = 1;
			current = rt->ui.dft_itms;
			printf("%p\n", current);
		}
	}
	if (!found || !current)
		return ;
	exec_button(rt, current);
}