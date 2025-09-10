/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:51 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/09 18:46:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mlxdata	*init_img(t_env *rt, t_mlxdata *img, int width, int height)
{
	img->img = mlx_new_image(rt->mlx.mlx, width, height);
	if (!img)
		error_exit(rt, "image error");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img->img);
}

void	putpixel(int x, int y, t_env *rt, t_color c)
{
	int	*iimg_addr;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	iimg_addr = (int *)rt->mlx.img.addr;
	iimg_addr[x + y * WIDTH] = (c.r << 16) | (c.g << 8) | c.b;
}

void	putpixel_ui(int x, int y, t_env *rt, t_color c)
{
	int	*iimg_addr;

	if (x < 0 || x >= UI_WIDTH || y < 0 || y >= UI_HEIGHT)
		return ;
	iimg_addr = (int *)rt->mlx.ui.addr;
	iimg_addr[x + y * UI_WIDTH] = (c.r << 16) | (c.g << 8) | c.b;
}

void	putpixel_ui_img(int x, int y, t_color c, void *img)
{
	char	*data_addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		*pixels;

	if (x < 0 || x >= UI_WIDTH || y < 0 || y >= UI_HEIGHT)
		return ;
	data_addr = mlx_get_data_addr(img, &bits_per_pixel, &line_size, &endian);
	pixels = (int *)data_addr;
	pixels[x + y * (line_size / 4)] = (c.r << 16) | (c.g << 8) | c.b;
}

void	putstr_ui(t_env *rt, int x, int y, char *str)
{
	mlx_string_put(rt->mlx.mlx, rt->mlx.win, WIDTH + x, y, 0xfffffff, str);
}
