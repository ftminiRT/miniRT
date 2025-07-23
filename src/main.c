/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:21:26 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:05:32 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hardcore_coding(t_env *rt)
{
	rt->ambient.brightness = 0.2;
	rt->ambient.color.r = 255;
	rt->ambient.color.g = 255;
	rt->ambient.color.b = 255;

	rt->cam.pos.x = -50;
	rt->cam.pos.y = 0;
	rt->cam.pos.z = 20;
	rt->cam.dir.x = 0;
	rt->cam.dir.y = 0;
	rt->cam.dir.z = 1;
	rt->cam.fov = 70;

	rt->spot.pos.x = -40;
	rt->spot.pos.y = 0;
	rt->spot.pos.z = 30;
	rt->spot.brightness = 0.7;
	rt->spot.color.r = 255;
	rt->spot.color.g = 255;
	rt->spot.color.b = 255;

	t_list_obj	*plane = malloc(sizeof(t_list_obj));
	plane->obj.type = OT_PLANE;
	plane->obj.plane.pt.x = 0;
	plane->obj.plane.pt.y = 0;
	plane->obj.plane.pt.z = 0;
	plane->obj.plane.n.x = 0;
	plane->obj.plane.n.y = 1.0;
	plane->obj.plane.n.z = 0;
	plane->obj.color.r = 10;
	plane->obj.color.g = 0;
	plane->obj.color.b = 255;

	t_list_obj	*sphere = malloc(sizeof(t_list_obj));
	sphere->obj.type = OT_SPHERE;
	sphere->obj.sphere.center.x = 0;
	sphere->obj.sphere.center.y = 0;
	sphere->obj.sphere.center.z = 20;
	sphere->obj.sphere.r = 10;
	sphere->obj.color.r = 255;
	sphere->obj.color.g = 0;
	sphere->obj.color.b = 0;

	t_list_obj	*cyl = malloc(sizeof(t_list_obj));
	cyl->obj.type = OT_CYL;
	cyl->obj.cyl.center.x = 50.0;
	cyl->obj.cyl.center.y = 0.0;
	cyl->obj.cyl.center.z = 20.6;
	cyl->obj.cyl.n.x = 0.0;
	cyl->obj.cyl.n.y = 0.0;
	cyl->obj.cyl.n.z = 1.0;
	cyl->obj.cyl.r = 14.2;
	cyl->obj.cyl.height = 21.42;
	cyl->obj.color.r = 10;
	cyl->obj.color.g = 0;
	cyl->obj.color.b = 255;

	plane->next = sphere;
	sphere->next = cyl;
	cyl->next = NULL;
	rt->objects = plane;
}

int	main(int ac, char **av)
{
	t_env	rt;

	(void) ac;
	(void) av;
	printf("hello world\n");
	if (ac < 2)
		return (printf("Argument file needed\n"), 0);
	rt_mlx_init(&rt.mlx);
	hardcore_coding(&rt);
	ray_trace(&rt);
	mlx_key_hook(rt.mlx.win, &key_pressed, &rt);
	mlx_loop(rt.mlx.mlx);
	clear_mlx(&rt);
	return (0);
}