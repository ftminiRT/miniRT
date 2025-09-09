/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_panes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 13:59:34 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-04 13:59:34 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_pane(t_env *rt, t_obj *obj)
{
	t_uipane	*new;
	t_uipane	*current;

	new = ft_calloc(1, sizeof(t_uipane));
	if (!new)
		return (1);
	new->type = obj->type;
	new->obj = obj;
	if (build_pane_events(rt, new))
		return (1);
	if (rt->ui.build_pane[obj->type](rt, new))
		return (1);
	current = rt->ui.stock;
	while (current->next)
		current = current->next;
	current->next = new;
	return (0);
}

int	create_pane_l(t_env *rt, t_light *light)
{
	t_uipane	*current;
	t_uipane	*last;

	current = ft_calloc(1, sizeof(t_uipane));
	if (!current)
		return (1);
	current->type = OT_LIGHT;
	current->light = light;
	if (build_pane_events(rt, current))
		return (1);
	if (rt->ui.build_pane[OT_LIGHT](rt, current))
		return (1);
	last = rt->ui.stock;
	while (last->next)
		last = last->next;
	last->next = current;
	return (0);
}

int	create_default_pane(t_env *rt)
{
	t_uipane	*dflt;

	dflt = ft_calloc(1, sizeof(t_uipane));
	if (!dflt)
		return (1);
	printf("%d, %s\n", __LINE__, __FILE__);
	fflush(stdout);
	dflt->cam = &rt->cam;
	dflt->light = &rt->ambient;
	dflt->type = OT_DFT;
	printf("%d, %s\n", __LINE__, __FILE__);
	fflush(stdout);
	if (build_pane_events(rt, dflt))
		return (1);
	printf("%d, %s\n", __LINE__, __FILE__);
	fflush(stdout);
	if (build_pane_dft(rt, dflt))
		return (1);
	printf("%d, %s\n", __LINE__, __FILE__);
	fflush(stdout);
	rt->ui.current = dflt;
	rt->ui.stock = dflt;
	return (0);
}

int	init_ui_panes(t_env *rt)
{
	t_obj	*current;
	t_light	*current_l;

	if (create_default_pane(rt))
		return (1);
	current = rt->objects;
	while (current)
	{
		if (create_pane(rt, current))
			return (1);
		current = current->next;
	}
	current_l = &rt->spot;
	while (current_l)
	{
		if (create_pane_l(rt, current_l))
			return (1);
		current_l = current_l->next;
	}
	return (0);
}
