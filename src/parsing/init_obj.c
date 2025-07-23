/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:35:58 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 19:13:34 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_list_obj	*create_object(t_env *rt)
{
	t_list_obj	*new;

	new = malloc(sizeof(t_list_obj));
	if (!new)
		return (perror("miniRT :"), NULL);
	new->next = NULL;
	if (rt->objects)
		new->next = rt->objects;
	rt->objects = new;
	return (new);
}

int	init_cylinder(char **args, t_env *rt)
{
	t_list_obj	*new;

	new = create_object(rt);
	if (!new)
		return (1);
	new->obj.type = OT_CYL;
	str_to_vec3(&new->obj.cyl.center, args[1]);
	str_to_vec3(&new->obj.cyl.n, args[2]);
	new->obj.cyl.r = ft_atod(args[3]) / 2;
	new->obj.cyl.height = ft_atod(args[4]);
	str_to_colors(&new->obj.color, args[5]);
	return (0);
}

int	init_plane(char **args, t_env *rt)
{
	t_list_obj	*new;

	new = create_object(rt);
	if (!new)
		return (1);
	new->obj.type = OT_PLAN;
	str_to_vec3(&new->obj.plan.pt, args[1]);
	str_to_vec3(&new->obj.plan.n, args[2]);
	str_to_colors(&new->obj.color, args[3]);
	return (0);
}

int	init_sphere(char **args, t_env *rt)
{
	t_list_obj	*new;

	new = create_object(rt);
	if (!new)
		return (1);
	new->obj.type = OT_SPHERE;
	str_to_vec3(&new->obj.sphere.center, args[1]);
	new->obj.sphere.r = ft_atod(args[2]) / 2;
	str_to_colors(&new->obj.color, args[3]);
	return (0);
}
