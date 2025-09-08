/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 15:49:54 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-04 15:49:54 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uipt pt(int x, int y)
{
    return ((t_uipt){x, y});
}

t_items setb(void *value, double factor, t_uipt pos, t_uipt scale)
{
	t_items	new;

	new.btn.factor = factor;
	new.btn.value = value;
	new.pos.x = pos.x;
	new.pos.y = pos.y;
	new.scale.x = scale.x;
	new.scale.y = scale.y;
	return (new);
}

void	add_back(t_items *new, t_uipane *pane)
{
	t_uipane *head;

	if (!pane)
	{
		pane = new;
		return ;
	}
	head = pane;
	while (pane->next)
		pane = pane->next;
	pane->next = new;
	pane = head;
}

int		add_btn(t_items og, t_uipane *pane)
{
	t_items *new;

	new = ft_calloc(1, sizeof(t_items));
	if (!new)
		return (1);
	new->btn.factor = og.btn.factor;
	new->btn.factor = og.btn.factor;
	new->btn.value = og.btn.value;
	new->pos.x = og.pos.x;
	new->pos.y = og.pos.y;
	new->scale.x = og.scale.x;
	new->scale.y = og.scale.y;
	new->next = NULL;
	add_back(new, pane);
}

