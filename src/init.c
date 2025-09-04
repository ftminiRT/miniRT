/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:48:44 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/04 23:11:24 by tbeauman         ###   ########.fr       */
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
	normalize_objs(rt);
	if (rt->ambient.brightness < 0)
		rt->ambient.brightness = 0;
	if (rt->ambient.brightness > 1)
		rt->ambient.brightness = 1;
	vec3_normalize(&rt->cam.dir);
	rt->ray.pt = rt->cam.pos;
}

void	normalize_objs(t_env *rt)
{
	t_obj	*objs;

	objs = rt->objects;
	while (objs)
	{
		if (!objs->shine)
			objs->shine = 100;
		if (objs->type == OT_PLANE || objs->type == OT_CYL || objs->type == OT_MOEB)
			vec3_normalize(&objs->n);
		if (objs->scal < EPSILON)
			objs->scal = EPSILON;
		if (objs->scal2 < 0.01 && objs->type == OT_TORE)
			objs->scal2 = 0.01;
		// if (objs->type == OT_PLANE)
		// 	objs->reflect = 0.8;
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
	rt->hit_object[OT_TORE] = hit_torus;
	rt->get_norm[OT_TORE] = torus_normal;
	rt->hit_object[OT_RING] = hit_ring;
	rt->get_norm[OT_RING] = ring_normal;
	rt->cam.is_set = 0;
	rt->ambient.is_set = 0;
	rt->spot.is_set = 0;
	rt->spot.next = NULL;
	rt->selected.type = CAM;
	rt->selected.cam = &rt->cam;
	rt->selected.spot = &rt->spot;
	rt->selected.amb = &rt->ambient;
	rt->selected.obj = NULL;
}