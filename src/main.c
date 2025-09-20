/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:55:52 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/04 23:38:01 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_objects(t_env *rt)
{
	t_obj	*head;
	t_obj	*next;

	head = rt->objects;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

int	main(int ac, char **av)
{
	t_env	rt;

	if (ac < 2)
		return (printf("Argument file needed\n"), 0);
	env_init(&rt);
	if (parsing(&rt, av[1]))
		return (1);
	rt_mlx_init(&rt.mlx);
	load_textures(&rt);
	if (ui_init(&rt))
		return (mrt_cleaner(&rt), 1);
	display_ui(&rt);
	ray_trace(&rt);
	mlx_mouse_hook(rt.mlx.win, &mouse_hook, &rt);
	mlx_key_hook(rt.mlx.win, &key_pressed, &rt);
	mlx_hook(rt.mlx.win, 17, 0, &close_window, &rt);
	mlx_loop(rt.mlx.mlx);
	mega_clean(&rt);
	return (0);
}
