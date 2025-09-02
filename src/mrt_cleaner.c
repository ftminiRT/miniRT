/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:21:17 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/02 22:50:53 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clean_obj(t_obj *current)
{
	t_obj *next;

	printf("%d %s\n", __LINE__, __FILE__);
	while (current)
	{
	printf("%d %s\n", __LINE__, __FILE__);
		next = current->next;
	printf("%d %s\n", __LINE__, __FILE__);
		free(current);
	printf("%d %s\n", __LINE__, __FILE__);
		current = next;
	printf("%d %s\n", __LINE__, __FILE__);
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
	printf("%d %s\n", __LINE__, __FILE__);
	clean_obj(rt->objects);
	printf("%d %s\n", __LINE__, __FILE__);
	clean_spots(rt->spot.next);
	printf("%d %s\n", __LINE__, __FILE__);
}