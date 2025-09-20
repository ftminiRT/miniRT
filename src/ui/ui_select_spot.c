/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_select_spot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 16:04:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 16:04:38 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_light	*tail(t_light *lights)
{
	if (!lights)
		return (NULL);
	while (lights->next)
		lights = lights->next;
	return (lights);
}

static t_light	*get_prev_light(t_env *rt, t_uipane *cur)
{
	t_light	*goal;
	t_light	*head;

	if (cur->type != OT_LIGHT)
		return (&rt->spot);
	goal = cur->light;
	head = &rt->spot;
	if (goal == head)
		goal = tail(head);
	else
	{
		while (head)
		{
			if (head->next == goal)
				goal = head;
			head = head->next;
		}
	}
	return (goal);
}

t_uipane	*get_prev_spot(t_env *rt)
{
	t_uipane	*stock;
	t_light		*goal;

	goal = get_prev_light(rt, rt->ui.current);
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
