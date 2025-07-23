/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:21:26 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:05:32 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_env	rt;

	(void) ac;
	(void) av;
	printf("hello world\n");
	if (ac < 2)
		return (printf("Argument file needed\n"), 0);
	rt_mlx_init(&rt.mlx);
	mlx_key_hook(rt.mlx.win, &key_pressed, &rt);
	mlx_loop(rt.mlx.mlx);
	clear_mlx(&rt);
	return (0);
}