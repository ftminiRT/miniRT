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

void	exec_button(t_items *itm)
{
	printf("trying to add %f to %f\n", itm->btn.factor, *itm->btn.value);
	*itm->btn.value = *itm->btn.value + itm->btn.factor;

}

int	hit_ui(int x, int y, t_items *itm)
{
	if ((x > itm->pos.x - (itm->scale.x / 2) && \
		x < itm->pos.x + (itm->scale.x / 2)) && \
		y > itm->pos.y - (itm->scale.y / 2) && \
		y < itm->pos.y + (itm->scale.y / 2))
		return (printf("hit\n"), 1);
	return (0);
}

void click_ui(int x, int y, t_env *rt)
{
	int 	found;
	t_items	*current;

	found = 0;
	current = rt->ui.current->itms;
	while (current)
	{
		found = hit_ui(x, y, current);
		if (found)
			break ;
		current = current->next;
	}
	if (!found)
		return ;
	exec_button(current);
}