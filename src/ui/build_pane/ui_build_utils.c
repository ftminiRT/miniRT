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

t_uipt	pt(int x, int y)
{
	return ((t_uipt){x, y});
}

t_items	setb(t_btn_data data, t_uipt pos, t_uipt scale)
{
	t_items	new;

	new.type = data.type;
	new.pos = pos;
	new.scale = scale;
	new.btn.value = data.value;
	new.btn.factor = data.factor;
	new.btn.v = data.v;
	new.function = NULL;
	return (new);
}

void	add_back(t_items *new, t_uipane *pane)
{
	t_items	*head;

	if (!pane->itms)
	{
		pane->itms = new;
		return ;
	}
	head = pane->itms;
	while (pane->itms->next)
		pane->itms = pane->itms->next;
	pane->itms->next = new;
	pane->itms = head;
}

void	build_local_basis(void *rt, t_basis *b)
{
	t_env	*e;

	e = (t_env *)rt;
	b->u = vec3_normalized(e->cam.dir);
	b->v = (t_vec3){0, 1, 0};
	if (fabs(vec3_dot(b->u, b->v)) > 0.999)
		b->v = (t_vec3){1, 0, 0};
	b->w = vec3_normalized(vec3_cross(b->u, b->v));
	b->v = vec3_cross(b->w, b->u);
}

int	add_btn(t_items og, t_uipane *pane)
{
	t_items	*new;

	new = ft_calloc(1, sizeof(t_items));
	if (!new)
		return (1);
	new->type = og.type;
	new->btn.factor = og.btn.factor;
	new->btn.value = og.btn.value;
	new->pos.x = og.pos.x;
	new->pos.y = og.pos.y;
	new->scale.x = og.scale.x;
	new->scale.y = og.scale.y;
	new->btn.v = og.btn.v;
	new->next = NULL;
	add_back(new, pane);
	return (0);
}
