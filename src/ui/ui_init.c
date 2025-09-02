/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-02 11:25:52 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-02 11:25:52 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_items *add_new_button(void *value, double factor, t_uipt pos, t_uipt scale)
{
	t_items	*new;

	new = malloc(sizeof(t_items));
	if (!new)
		return (NULL);
	new->btn.linkwin = NULL;
	new->btn.factor = factor;
	new->btn.value = value;
	new->pos.x = pos.x;
	new->pos.y = pos.y;
	new->scale.x = scale.x;
	new->scale.y = scale.y;
	return (new);
}

int	add_default_buttons(t_env *rt)
{
	t_uiwin *win;

	win = rt->ui.current;
	win->itms = add_new_button(&rt->ambient.brightness, 0.1, (t_uipt){100,100}, (t_uipt){30,30});
	if (!win->itms)
		return (1);
	putpixel_ui(100, 100, rt, (t_color){255, 0, 0});
	return (0);
}

int	create_default_win(t_env *rt)
{
	t_uiwin *dflt;

	dflt = ft_calloc(1, sizeof(t_uiwin));
	if (!dflt)
		return (1);
	dflt->cam = &rt->cam;
	dflt->light = &rt->ambient;
	dflt->type = UIT_DEFAULT;
	rt->ui.current = dflt;
	rt->ui.stock = dflt;
	return (0);
}

int ui_init(t_env *rt)
{

	if (create_default_win(rt) || add_default_buttons(rt))
		return (1);
	if (!rt->ui.itms)
		return (1);
	return (0);
}