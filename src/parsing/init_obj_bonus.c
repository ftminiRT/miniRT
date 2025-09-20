/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:39:29 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/04 23:27:31 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_cone(char **args, t_env *rt)
{
	t_obj	*new;
	size_t	arg_len;

	arg_len = count_arg(args);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_CONE;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (str_to_vec3(&new->n, args[2]) || check_norm(new->n))
		return (1);
	if (!str_is_double(args[3]))
		return (1);
	new->scal = ft_atod(args[3]);
	if (new->scal <= 0 || new->scal >= 180)
		return (1);
	if (str_to_colors(&new->color, args[4]))
		return (1);
	if (arg_len >= 6)
		return (set_bonus_attributes(&args[5], rt, new));
	return (0);
}

int	init_tore(char **args, t_env *rt)
{
	t_obj	*new;
	size_t	arg_len;

	arg_len = count_arg(args);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_TORE;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (str_to_vec3(&new->n, args[2]) || check_norm(new->n))
		return (1);
	if (!str_is_double(args[3]) || !str_is_double(args[4]))
		return (1);
	new->scal = ft_atod(args[3]);
	new->scal2 = ft_atod(args[4]);
	if (str_to_colors(&new->color, args[5]))
		return (1);
	if (arg_len >= 7)
		return (set_bonus_attributes(&args[6], rt, new));
	return (0);
}

int	init_ring(char **args, t_env *rt)
{
	t_obj	*new;
	size_t	arg_len;

	arg_len = count_arg(args);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_RING;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (str_to_vec3(&new->n, args[2]) || check_norm(new->n))
		return (1);
	if (!str_is_double(args[3]) || !str_is_double(args[4])
		|| !str_is_double(args[5]))
		return (1);
	new->scal = ft_atod(args[3]);
	new->scal2 = ft_atod(args[4]);
	new->scal3 = ft_atod(args[5]);
	if (str_to_colors(&new->color, args[6]))
		return (1);
	if (arg_len >= 8)
		return (set_bonus_attributes(&args[7], rt, new));
	return (0);
}

int	init_moebius(char **args, t_env *rt)
{
	t_obj	*new;
	size_t	arg_len;

	arg_len = count_arg(args);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_MOEB;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (!str_is_double(args[2]) || !str_is_double(args[3]) \
		|| !str_is_double(args[4]))
		return (1);
	new->scal = ft_atod(args[2]);
	new->scal2 = ft_atod(args[3]);
	new->max = ft_atod(args[4]);
	if (str_to_vec3(&new->n, args[5]) || check_norm(new->n))
		return (1);
	if (str_to_colors(&new->color, args[6]))
		return (1);
	if (arg_len >= 8)
		return (set_bonus_attributes(&args[7], rt, new));
	return (0);
}
