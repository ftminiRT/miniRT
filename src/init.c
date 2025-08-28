/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:48:44 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 19:20:02 by tbeauman         ###   ########.fr       */
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
	rt->hit_object[OT_SPHERE] = hit_sphere;
	rt->get_norm[OT_SPHERE] = sphere_normal;
	rt->hit_object[OT_CYL] = hit_cylinder;
	rt->get_norm[OT_CYL] = cylinder_normal;
	rt->hit_object[OT_PLANE] = hit_plane;
	rt->get_norm[OT_PLANE] = plane_normal;
	rt->hit_object[OT_MOEB] = hit_moebius;
	rt->get_norm[OT_MOEB] = moebius_normal;
	rt->cam.is_set = 0;
	rt->ambient.is_set = 0;
	rt->spot.is_set = 0;
	rt->spot.next = NULL;
}