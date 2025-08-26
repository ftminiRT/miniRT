/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:48:44 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/26 14:44:28 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_mlx_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		error_exit("connection to mlx error");
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		error_exit("window error");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->mlx)
		error_exit("image error");
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
}

void	env_init(t_env *rt)
{
	t_objtype i;

	i = OT_SPHERE;
	rt->hit_object[i] = hit_sphere;
	rt->cam.is_set = 0;
	rt->ambient.is_set = 0;
	rt->spot.is_set = 0;
	while (++i != sizeof(t_objtype))
	{
		if (i == OT_CYL)
			rt->hit_object[i] = hit_cylinder;
		if (i == OT_PLANE)
			rt->hit_object[i] = hit_plane;
	}
}