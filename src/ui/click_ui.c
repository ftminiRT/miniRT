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

t_uipane 	*get_default_pane_addr(t_env *rt)
{
	t_uipane	*stock;

	stock = rt->ui.stock;
	while (stock)
	{
		if (stock->type == OT_DFT)
			return (stock);
		stock = stock->next;
	}
	return (NULL);
}

t_uipane	*get_prev_spot(t_env *rt)
{
	t_uipane	*stock;
	t_uipane	*cur;
	t_light		*goal;
	t_light		*head;

	cur = rt->ui.current;
	if (cur->type == OT_LIGHT)
	{
		goal = cur->light;
		head = &rt->spot;
		if (goal == head)
		{
			while (head->next)
				head = head->next;
			goal = head;
		}
		else
		{
			while (head)
			{
				if (head->next == goal)
					goal = head;
				head = head->next;
			}
		}
	}
	else
		goal = &rt->spot;
	stock = rt->ui.stock;
	while (stock)
	{
		if (stock->type == OT_LIGHT && stock->light == goal)
			return (stock);
		stock = stock->next;
	}
	return (NULL);
}


t_uipane	*get_next_spot(t_env *rt)
{
	t_uipane	*stock;
	t_uipane	*cur;
	t_light		*goal;

	cur = rt->ui.current;
	if (cur->type == OT_LIGHT)
	{
		if (cur->light && cur->light->next)
			goal = cur->light->next;
		else
			goal = &rt->spot;
	}
	else
		goal = &rt->spot;
	stock = rt->ui.stock;
	while (stock)
	{
		if (stock->type == OT_LIGHT && stock->light == goal)
			return (stock);
		stock = stock->next;
	}
	return (NULL);
}

t_uipane	*get_spot(t_env *rt)
{
	t_uipane	*stock;
	t_uipane	*cur;
	t_light		*goal;

	cur = rt->ui.current;
	if (cur->type == OT_LIGHT)
		return (cur);
	goal = &rt->spot;
	stock = rt->ui.stock;
	while (stock)
	{
		if (stock->type == OT_LIGHT && stock->light == goal)
			return (stock);
		stock = stock->next;
	}
	return (NULL);
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
	else if (itm->type == UIT_SEL_BTN && itm->btn.factor == -1)
		rt->ui.current = get_prev_spot(rt);
	else if (itm->type == UIT_SEL_BTN && itm->btn.factor == 1)
		rt->ui.current = get_next_spot(rt);
	else if (itm->type == UIT_SPOT_BTN && itm->type != OT_LIGHT)
		rt->ui.current = get_spot(rt);
	else if (itm->type == UIT_CAM_BTN)
		rt->ui.current = get_default_pane_addr(rt);
	else if (itm->type == UIT_EXPORT_BTN)
		export_to_rt(rt);
	else if (itm->type == UIT_RND_BTN)
	{
		rt->render = !rt->render;
		rt->basicrt = !rt->basicrt;
		if (!rt->render)
			ray_trace(rt);
	}
	else if (itm->function)
		itm->function(rt);
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