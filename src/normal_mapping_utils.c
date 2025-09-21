/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_mapping_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:43:30 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:43:30 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	load_normal_map(void *mlx_ptr, t_obj *obj, char *filename)
{
	if (!mlx_ptr || !obj || !filename)
		return (0);
	obj->normal_map_img = mlx_xpm_file_to_image(mlx_ptr, filename,
			&obj->normal_map_width, &obj->normal_map_height);
	if (!obj->normal_map_img)
	{
		write_error("can't load ", filename);
		return (0);
	}
	obj->normal_map_data = mlx_get_data_addr(obj->normal_map_img,
			&obj->normal_map_bpp, &obj->normal_map_size_line,
			&obj->normal_map_endian);
	if (!obj->normal_map_data)
	{
		mlx_destroy_image(mlx_ptr, obj->normal_map_img);
		obj->normal_map_img = NULL;
		return (0);
	}
	return (1);
}

void	free_normal_map(void *mlx_ptr, t_obj *obj)
{
	if (!obj)
		return ;
	(void)mlx_ptr;
	obj->normal_map_img = NULL;
	obj->normal_map_data = NULL;
	obj->normal_map_width = 0;
	obj->normal_map_height = 0;
	obj->normal_map_bpp = 0;
	obj->normal_map_size_line = 0;
	obj->normal_map_endian = 0;
}

t_vec3	sample_normal_map(t_obj *obj, float u, float v)
{
	t_vec3	map_normal;
	char	*data;
	int		x;
	int		y;
	int		pixel;

	if (!obj->normal_map_data)
		return ((t_vec3){0.0, 0.0, 1.0});
	u = u - floor(u);
	v = v - floor(v);
	if (u < 0)
		u += 1.0;
	if (v < 0)
		v += 1.0;
	x = (int)(u * obj->normal_map_width) % obj->normal_map_width;
	y = (int)(v * obj->normal_map_height) % obj->normal_map_height;
	data = (char *)obj->normal_map_data;
	pixel = *(int *)(data + (y * obj->normal_map_size_line + x
				* (obj->normal_map_bpp / 8)));
	map_normal.x = ((pixel & 0xFF0000) >> 16) / 255.0 * 2.0 - 1.0;
	map_normal.y = ((pixel & 0x00FF00) >> 8) / 255.0 * 2.0 - 1.0;
	map_normal.z = (pixel & 0x0000FF) / 255.0 * 2.0 - 1.0;
	return (map_normal);
}
