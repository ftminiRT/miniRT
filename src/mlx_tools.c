/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:51 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/26 15:16:52 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mlxdata	*init_img(t_mlx *mlx, t_mlxdata *img, int width, int height)
{
	img->img = mlx_new_image(mlx->mlx, width, height);
	if (!img)
		error_exit("image error");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	return (img->img);
}

void	putpixel(int x, int y, t_env *rt, t_color c)
{
	int	*iimg_addr;

	if (x < 0 || x >= WIDTH|| y < 0 || y >= HEIGHT)
		return ;
	iimg_addr = (int *)rt->mlx.img.addr;
	iimg_addr[x + y * WIDTH] = (c.r << 16) | (c.g << 8) | c.b;
}

void	putpixel_ui(int x, int y, t_env *rt, t_color c)
{
	int	*iimg_addr;

	if (x < 0 || x >= UI_WIDTH|| y < 0 || y >= UI_HEIGHT)
		return ;
	iimg_addr = (int *)rt->mlx.ui.addr;
	iimg_addr[x + y * UI_WIDTH] = (c.r << 16) | (c.g << 8) | c.b;
}

void	putpixel_ui_img(int x, int y, t_color c, void *img)
{
	int	*iimg_addr;

	if (x < 0 || x >= UI_WIDTH|| y < 0 || y >= UI_HEIGHT)
		return ;
	iimg_addr = (int *)img;
	iimg_addr[x + y * UI_WIDTH] = (c.r << 16) | (c.g << 8) | c.b;
}