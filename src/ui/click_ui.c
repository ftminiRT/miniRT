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

void	exec_button(t_env *rt, t_items *itm)
{
	if (itm->type == UIT_SCL_BTN)
	{
		printf("bouton\n");
		*itm->btn.value = *itm->btn.value + itm->btn.factor;
	}
	else
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