/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:21:17 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 19:12:20 by tcoeffet         ###   ########.fr       */
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
	t_light	*next;

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

/* void	close_imgs(t_env *rt)
{
	size_t	i;
	char	*data_addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;

	i = 0;
	while (1)
	{
		data_addr = mlx_get_data_addr(rt->ui.pane_img[i], \
			&bits_per_pixel, &line_size, &endian);
		mlx_destroy_image(rt->mlx.mlx, (void *)data_addr);
		i = (i + 1) % OBJTYPENUMBER;
		if (!i)
			return ;
	}
} */

/* void	close_imgs(t_env *rt)
{
	size_t	i;

	i = 0;
	while (1)
	{
		mlx_destroy_image(rt->mlx.mlx, rt->ui.pane_img[i]);
		i = (i + 1) % OBJTYPENUMBER;
		if (!i)
			return ;
	}
} */

void	clean_panes(t_env *rt)
{
	t_uipane	*cpane;
	t_items		*citm;
	void		*tmp;

	cpane = rt->ui.stock;
	while (cpane)
	{
		citm = cpane->itms;
		while (citm)
		{
			tmp = citm;
			citm = citm->next;
			free(tmp);
		}
		tmp = cpane;
		cpane = cpane->next;
		free(tmp);
	}
}

void	mrt_cleaner(t_env *rt)
{
	printf("MRT CLEANER //////\n");
	// close_imgs(rt);
	clean_panes(rt);
	// printf("%d, %s\n", __LINE__, __FILE__);
	clean_obj(rt->objects);
	// printf("%d, %s\n", __LINE__, __FILE__);
	clean_spots(rt->spot.next);
	// printf("%d, %s\n", __LINE__, __FILE__);
}