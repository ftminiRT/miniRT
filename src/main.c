/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:21:26 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/08/26 15:23:09 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	debug_print_object(t_obj obj)
{
	if (obj.type == OT_SPHERE)
	{
		printf("SPHERE ----\n");
		printf("pos = %f, %f, %f\n", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("r = %f\n", obj.scal);
	}
	if (obj.type == OT_PLANE)
	{
		printf("PLANE ----\n");
		printf("pt = %f, %f, %f\n", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("n = %f, %f, %f\n", obj.n.x, obj.n.y, obj.n.z);
	}
	if (obj.type == OT_CYL)
	{
		printf("CYLINDER ----\n");
		printf("center = %f, %f, %f\n", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("n = %f, %f, %f\n", obj.n.x, obj.n.y, obj.n.z);
		printf("r = %f\n", obj.scal);
		printf("height = %f\n", obj.scal2);
	}
	printf("color = %d, %d, %d\n\n\n", obj.color.r, obj.color.g, obj.color.b);
}

void	debug_print_set(t_env *rt)
{
	t_obj	*obj;

	printf("\n\nDEBUG : SET\n///////////\n");
	printf("set amb light ---- \n");
	printf("brightness = %f\n", rt->ambient.brightness);
	printf("color = %d, %d, %d\n\n\n", rt->ambient.color.r, rt->ambient.color.g,
		rt->ambient.color.b);
	/////
	printf("set cam ---- \n");
	printf("pos = %f, %f, %f\n", rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z);
	printf("dir = %f, %f, %f\n", rt->cam.dir.x, rt->cam.dir.y, rt->cam.dir.z);
	printf("fov = %d\n\n\n", rt->cam.fov);
	/////
	printf("set spot light ---- \n");
	printf("pos = %f, %f, %f\n", rt->spot.pos.x, rt->spot.pos.y,
		rt->spot.pos.z);
	printf("brightness = %f\n", rt->spot.brightness);
	printf("color = %d, %d, %d\n\n\n", rt->spot.color.r, rt->spot.color.g,
		rt->spot.color.b);
	/////
	printf("DEBUG : OBJECTS\n///////////\n");
	obj = rt->objects;
	while (obj)
	{
		debug_print_object(*obj);
		obj = obj->next;
	}
}

void	clear_objects(t_env *rt)
{
	t_obj	*head;
	t_obj	*next;

	head = rt->objects;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

int	main(int ac, char **av)
{
	t_env	rt;

	if (ac < 2)
		return (printf("Argument file needed\n"), 0);
	env_init(&rt);
	if (parsing(&rt, av[1]))
		return (1);
	debug_print_set(&rt);
	rt_mlx_init(&rt.mlx);
	ray_trace(&rt);
	mlx_key_hook(rt.mlx.win, &key_pressed, &rt);
	mlx_loop(rt.mlx.mlx);
	clear_mlx(&rt);
	return (0);
}
