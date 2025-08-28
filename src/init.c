/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:48:44 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 18:46:02 by tbeauman         ###   ########.fr       */
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

void	init_rt(t_env *rt)
{
	normalize_objs_normal(rt);
	vec3_normalize(&rt->cam.dir);
	rt->ray.pt = rt->cam.pos;
}

void	normalize_objs_normal(t_env *rt)
{
	t_obj	*objs;

	objs = rt->objects;
	while (objs)
	{
		objs->shine = 100;
		if (objs->type == OT_PLANE || objs->type == OT_CYL || objs->type == OT_MOEB)
			vec3_normalize(&objs->n);
		if (objs->type == OT_MOEB)
			objs->max = 5;
		objs = objs->next;
	}
}

void	env_init(t_env *rt)
{
	t_objtype i;

	i = OT_SPHERE;
	rt->hit_object[i] = hit_sphere;
	rt->get_norm[i] = sphere_normal;
	rt->cam.is_set = 0;
	rt->ambient.is_set = 0;
	rt->spot.is_set = 0;
	rt->spot.next = NULL;
	while (++i != sizeof(t_objtype))
	{
		if (i == OT_CYL)
		{
			rt->hit_object[i] = hit_cylinder;
			rt->get_norm[i] = cylinder_normal;
		}
		if (i == OT_PLANE)
		{
			rt->hit_object[i] = hit_plane;
			rt->get_norm[i] = plane_normal;
		}
		if (i == OT_MOEB)
		{
			rt->hit_object[i] = hit_moebius;
			rt->get_norm[i] = moebius_normal;
		}
	}
}