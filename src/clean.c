/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:17:07 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/02 22:49:59 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clear_mlx(t_env *rt)
{
	printf("%d %s\n", __LINE__, __FILE__);
	mlx_destroy_window(rt->mlx.mlx, rt->mlx.win);
	printf("%d %s\n", __LINE__, __FILE__);
	mlx_destroy_image(rt->mlx.mlx, rt->mlx.img.img);
	printf("%d %s\n", __LINE__, __FILE__);
	mlx_destroy_display(rt->mlx.mlx);
	printf("%d %s\n", __LINE__, __FILE__);
	free(rt->mlx.mlx);
	return (1);
}
