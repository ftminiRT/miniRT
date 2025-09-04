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
	t_uipane	*current;

	current = ft_calloc(1, sizeof(t_uipane));
	if (!current)
		return (1);
	if (rt->ui.build_pane[obj->type](rt, current))
		return (1);
	return (0);
}

int	create_default_pane(t_env *rt)
{
	t_uipane *dflt;

	dflt = ft_calloc(1, sizeof(t_uipane));
	if (!dflt)
		return (1);
	dflt->cam = &rt->cam;
	dflt->light = &rt->ambient;
	dflt->type = UIT_DEFAULT;
	rt->ui.current = dflt;
	rt->ui.stock = dflt;
	return (0);
}

int init_ui_panes(t_env *rt)
{
	t_obj	*current;

	if (create_default_pane(rt))
		return (1);
	current = rt->objects;
	while (current)
	{
		if (create_pane(rt, current))
			return (1);
		current = current->next;
	}	
	return (0);
}