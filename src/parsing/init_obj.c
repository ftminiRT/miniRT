/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:35:58 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/08/27 17:05:47 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*create_object(t_env *rt)
{
	t_obj	*new;
	t_obj	*current;

	new = ft_calloc(1, sizeof(t_obj));
	if (!new)
		return (perror("Error :\n"), NULL);
	new->next = NULL;
	current = rt->objects;
	if (!rt->objects)
		rt->objects = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

int	init_cylinder(char **args, t_env *rt)
{
	t_obj	*new;
	size_t	arg_len;

	arg_len = count_arg(args);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_CYL;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (str_to_vec3(&new->n, args[2]))
		return (1);
	if (check_norm(new->n))
		return (1);
	if (!str_is_double(args[3]) || !str_is_double(args[4]))
		return (1);
	new->scal = ft_atod(args[3]) / 2;
	new->scal2 = ft_atod(args[4]);
	if (str_to_colors(&new->color, args[5]))
		return (1);
	if (arg_len >= 7)
		return (set_bonus_attributes(&args[6], rt, new));
	return (0);
}

int	init_plane(char **args, t_env *rt)
{
	t_obj	*new;
	size_t	arg_len;

	arg_len = count_arg(args);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_PLANE;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (str_to_vec3(&new->n, args[2]))
		return (1);
	if (check_norm(new->n))
		return (1);
	if (str_to_colors(&new->color, args[3]))
		return (1);
	if (arg_len >= 5)
		return (set_bonus_attributes(&args[4], rt, new));
	return (0);
}

int	init_sphere(char **args, t_env *rt)
{
	t_obj	*new;
	size_t	arg_len;

	arg_len = count_arg(args);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_SPHERE;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (!str_is_double(args[2]))
		return (1);
	new->scal = ft_atod(args[2]) / 2;
	if (str_to_colors(&new->color, args[3]))
		return (1);
	if (arg_len >= 5)
		return (set_bonus_attributes(&args[4], rt, new));
	return (0);
}
