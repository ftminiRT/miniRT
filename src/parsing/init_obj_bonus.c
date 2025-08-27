/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:39:29 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/08/27 15:44:15 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_cone(char **args, t_env *rt)
{
	t_obj	*new;

	if (count_arg(args) != 5)
		return (1);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_CONE;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (str_to_vec3(&new->n, args[2]) || check_norm(new->n))
		return (1);
	new->a = ft_atod(args[3]);
	if (new->a < 0 || new->a > 360)
		return (1);
	if (str_to_colors(&new->color, args[4]))
		return (1);
	return (0);
}

int	init_tore(char **args, t_env *rt)
{
	t_obj	*new;

	if (count_arg(args) != 6)
		return (1);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_TORE;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (str_to_vec3(&new->n, args[2]) || check_norm(new->n))
		return (1);
	new->scal = ft_atod(args[3]);
	new->scal2 = ft_atod(args[4]);
}