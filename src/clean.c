/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:17:07 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/26 15:17:08 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clear_mlx(t_env *rt)
{
	mlx_destroy_window(rt->mlx.mlx, rt->mlx.win);
	mlx_destroy_image(rt->mlx.mlx, rt->mlx.img.img);
	mlx_destroy_display(rt->mlx.mlx);
	free(rt->mlx.mlx);
	return (1);
}
