/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:35:58 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 19:59:56 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*create_object(t_env *rt)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
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
	t_obj	*new;

	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_CYL;
	str_to_vec3(&new->pt, args[1]);
	str_to_vec3(&new->n, args[2]);
	new->scal = ft_atod(args[3]) / 2;
	new->scal2 = ft_atod(args[4]);
	str_to_colors(&new->color, args[5]);
	return (0);
}

int	init_plane(char **args, t_env *rt)
{
	t_obj	*new;

	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_PLANE;
	str_to_vec3(&new->pt, args[1]);
	str_to_vec3(&new->n, args[2]);
	str_to_colors(&new->color, args[3]);
	return (0);
}

int	init_sphere(char **args, t_env *rt)
{
	t_obj	*new;

	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_SPHERE;
	str_to_vec3(&new->pt, args[1]);
	new->scal = ft_atod(args[2]) / 2;
	str_to_colors(&new->color, args[3]);
	return (0);
}
