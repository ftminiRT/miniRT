/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:35:25 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:35:25 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_bonus_attributes(t_obj obj)
{
	printf("s:%f ", obj.shine);
	printf("r:%f", obj.reflect);
	if (obj.checkered)
		printf(" t:checkered");
	else if (obj.texture_filename)
		printf(" t:%s", obj.texture_filename);
	if (obj.normal_map_filename)
		printf(" n:%s", obj.normal_map_filename);
}

void	print_bonus_object(t_obj obj)
{
	if (obj.type == OT_CONE)
	{
		printf("co %f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f %f", obj.n.x, obj.n.y, obj.n.z, obj.a);
	}
	else if (obj.type == OT_TORE)
	{
		printf("to %f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
		printf("%f %f ", obj.scal, obj.scal2);
	}
	else if (obj.type == OT_RING)
	{
		printf("ri %f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
		printf("%f %f %f ", obj.scal, obj.scal2, obj.scal3);
	}
	else if (obj.type == OT_MOEB)
	{
		printf("mo %f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f %f %f ", obj.scal, obj.scal2, obj.max);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
	}
	else
		printf("error\n");
}

void	print_object(t_obj obj)
{
	if (obj.type == OT_SPHERE)
		printf("sp %f,%f,%f %f ", obj.pt.x, obj.pt.y, obj.pt.z, 2 * obj.scal);
	else if (obj.type == OT_PLANE)
	{
		printf("pl %f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
	}
	else if (obj.type == OT_CYL)
	{
		printf("cy %f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
		printf("%f ", 2 * obj.scal);
		printf("%f ", obj.scal2);
	}
	else if (obj.type == OT_CONE)
	{
		printf("co %f,%f,%f ", obj.pt.x, obj.pt.y, obj.pt.z);
		printf("%f,%f,%f ", obj.n.x, obj.n.y, obj.n.z);
		printf("%f ", obj.scal);
	}
	printf("%d,%d,%d ", obj.color.r, obj.color.g, obj.color.b);
	if (BONUS)
		print_bonus_attributes(obj);
	printf("\n");
}

void	print_set(t_env *rt)
{
	t_obj	*obj;
	t_light	*spots;

	printf("A %f ", rt->ambient.brightness);
	printf("%d,%d,%d\n", rt->ambient.color.r, rt->ambient.color.g,
		rt->ambient.color.b);
	printf("C %f,%f,%f ", rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z);
	printf("%f,%f,%f ", rt->cam.dir.x, rt->cam.dir.y, rt->cam.dir.z);
	printf("%d\n", rt->cam.fov);
	spots = &rt->spot;
	while (spots)
	{
		printf("L %f,%f,%f ", spots->pos.x, spots->pos.y,
			spots->pos.z);
		printf("%f ", spots->brightness);
		printf("%d,%d,%d\n", spots->color.r, spots->color.g,
			spots->color.b);
		spots = spots->next;
	}
	obj = rt->objects;
	while (obj)
	{
		print_object(*obj);
		obj = obj->next;
	}
}
