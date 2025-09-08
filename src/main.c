/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:55:52 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/04 23:38:01 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	debug_print_bonus_object(t_obj obj)
{
	if (obj.type == OT_CONE)
	{
		printf("co ");
		printf("%f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
		printf("%f", obj.a);
	}
	else if (obj.type == OT_TORE)
	{
		printf("to ");
		printf("%f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
		printf("%f ", obj.scal);
		printf("%f ", obj.scal2);
	}
	else if (obj.type == OT_RING)
	{
		printf("ri %f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
		printf("%f ", obj.scal);
		printf("%f ", obj.scal2);
		printf("%f ", obj.scal3);
	}
	else if (obj.type == OT_MOEB)
	{
		printf("mo ");
		printf("%f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f ", obj.scal);
		printf("%f ", obj.scal2);
		printf("%f ", obj.max);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
	}
	else
	{
		printf("error\n");
	}
}

void	debug_print_object(t_obj obj)
{
	if (obj.type == OT_SPHERE)
	{
		printf("sp ");
		printf("%f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f ", 2 * obj.scal);
	}
	else if (obj.type == OT_PLANE)
	{
		printf("pl ");
		printf("%f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
	}
	else if (obj.type == OT_CYL)
	{
		printf("cy ");
		printf("%f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
		printf("%f ", 2 * obj.scal);
		printf("%f ", obj.scal2);
	}
	else
		debug_print_bonus_object(obj);
	printf("%d,%d,%d ", obj.color.r, obj.color.g, obj.color.b);
	if (BONUS)
	{	
		printf("s:%f ", obj.shine);
		printf("r:%f", obj.reflect);
		if (obj.checkered)
			printf(" t:checkered");
		else if (obj.texture_filename)
			printf(" t:%s", obj.texture_filename);
		if (obj.normal_map_filename)
			printf(" n:%s",obj.normal_map_filename);
	}
	printf("\n");
}

void	debug_print_set(t_env *rt)
{
	t_obj	*obj;
	t_light	*spots;

	printf("A ");
	printf("%f ", rt->ambient.brightness);
	printf("%d,%d,%d\n", rt->ambient.color.r, rt->ambient.color.g,
		rt->ambient.color.b);
	/////
	printf("C ");
	printf("%f,%f,%f ", rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z);
	printf("%f,%f,%f ", rt->cam.dir.x, rt->cam.dir.y, rt->cam.dir.z);
	printf("%d\n", rt->cam.fov);
	/////
	spots = &rt->spot;
	while (spots)
	{
		printf("L ");
		printf("%f,%f,%f ", spots->pos.x, spots->pos.y,
			spots->pos.z);
		printf("%f ", spots->brightness);
		printf("%d,%d,%d\n", spots->color.r, spots->color.g,
			spots->color.b);
		spots = spots->next;
	}
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
		return (printf("%d, %s\n",__LINE__, __FILE__), printf("Argument file needed\n"), 0);
	env_init(&rt);
	if (parsing(&rt, av[1]))
		return (printf("%d, %s\n",__LINE__, __FILE__),  1);
	rt_mlx_init(&rt.mlx);
	load_textures(&rt);
	debug_print_set(&rt);
	display_ui(&rt);
	if (ui_init(&rt))
		return (printf("%d, %s\n",__LINE__, __FILE__), mrt_cleaner(&rt), 1);
	ray_trace(&rt);
	mlx_mouse_hook(rt.mlx.win, &mouse_hook, &rt);
	mlx_key_hook(rt.mlx.win, &key_pressed, &rt);
	mlx_hook(rt.mlx.win, 17, 0, &close_window, &rt);
	mlx_loop(rt.mlx.mlx);
	mega_clean(&rt);
	return (0);
}
