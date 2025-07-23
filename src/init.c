/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:48:44 by tbeauman          #+#    #+#             */
/*   Updated: 2025/07/23 15:48:46 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    rt_mlx_init(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        error_exit("connection to mlx error");
    mlx->win = mlx_new_window(mlx->mlx, 1337, 1337, "miniRT");
    if (!mlx->win)
        error_exit("window error");
    mlx->img.img = mlx_new_image(mlx->mlx, 1337, 1337);
    if (!mlx->mlx)
        error_exit("image error");
    mlx->img.addr = mlx_get_data_addr(mlx->img.img,
        &mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
}
