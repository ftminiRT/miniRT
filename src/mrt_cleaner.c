/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_cleaner                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-01 15:21:17 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-01 15:21:17 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clean_obj(t_obj *current)
{
	t_obj *next;

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

static void	clean_spots(t_light *current)
{
	t_light *next;

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	mrt_cleaner(t_env *rt)
{
	clean_obj(rt->objects);
	clean_spots(&rt->spot);
	free(rt);
}