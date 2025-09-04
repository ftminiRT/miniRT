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

void	clear_all_textures(t_env *rt)
{
	t_obj *obj;

	obj = rt->objects;
	while (obj)
	{
		if (obj->texture_img)
		{
			mlx_destroy_image(rt->mlx.mlx, obj->texture_img);
			obj->texture_img = NULL;
		}
		if (obj->texture_filename)
			free(obj->texture_filename);
		if (obj->normal_map_img)
		{
			mlx_destroy_image(rt->mlx.mlx, obj->normal_map_img);
			obj->normal_map_img = NULL;
		}
		if (obj->normal_map_filename)
			free(obj->normal_map_filename);

		obj = obj->next;
	}
}

int	clear_mlx(t_env *rt)
{
	clear_all_textures(rt);
	mlx_destroy_window(rt->mlx.mlx, rt->mlx.win);
	mlx_destroy_image(rt->mlx.mlx, rt->mlx.img.img);
	mlx_destroy_display(rt->mlx.mlx);
	free(rt->mlx.mlx);
	return (1);
}
