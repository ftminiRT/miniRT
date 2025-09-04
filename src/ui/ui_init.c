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
	t_uipane *pane;

	pane = rt->ui.current;
	pane->itms = add_new_button(&rt->ambient.brightness, 0.1, (t_uipt){100,100}, (t_uipt){30,30});
	if (!pane->itms)
		return (1);
	putpixel_ui(100, 100, rt, (t_color){255, 0, 0});
	return (0);
}



int ui_init(t_env *rt)
{
	rt->ui.build_pane[OT_CONE] = build_pane_co;
	rt->ui.build_pane[OT_CYL] = build_pane_cyl;
	rt->ui.build_pane[OT_MOEB] = build_pane_mo;
	rt->ui.build_pane[OT_PLANE] = build_pane_pl;
	rt->ui.build_pane[OT_SPHERE] = build_pane_sp;
	rt->ui.build_pane[OT_TORE] = build_pane_to;
	if (init_ui_panes(rt))
		return (1);
	if (!rt->ui.itms)
		return (1);
	return (0);
}