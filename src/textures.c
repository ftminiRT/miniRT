/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:51:33 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:51:33 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	load_texture(void *mlx_ptr, t_obj *obj, char *filename)
{
	if (!mlx_ptr || !obj || !filename)
		return (0);
	obj->texture_img = mlx_xpm_file_to_image(mlx_ptr, filename,
			&obj->texture_w, &obj->texture_h);
	if (!obj->texture_img)
		return (0);
	obj->texture_data = mlx_get_data_addr(obj->texture_img, &obj->texture_bpp,
			&obj->texture_size_line, &obj->texture_endian);
	return (1);
}

void	load_textures(t_env *rt)
{
	t_obj	*obj;

	obj = rt->objects;
	while (obj)
	{
		if (obj->texture_filename)
		{
			if (!load_texture(rt->mlx.mlx, obj, obj->texture_filename))
				obj->texture_data = NULL;
		}
		if (obj->normal_map_filename)
		{
			if (!load_normal_map(rt->mlx.mlx, obj, obj->normal_map_filename))
				obj->normal_map_data = NULL;
		}
		obj = obj->next;
	}
}

void	free_texture(void *mlx_ptr, t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->texture_img)
	{
		mlx_destroy_image(mlx_ptr, obj->texture_img);
		obj->texture_img = NULL;
	}
	obj->texture_data = NULL;
	obj->texture_w = 0;
	obj->texture_h = 0;
	obj->texture_bpp = 0;
	obj->texture_size_line = 0;
	obj->texture_endian = 0;
}
