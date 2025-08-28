/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:39:29 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/08/28 18:20:33 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_cone(char **args, t_env *rt)
{
	t_obj	*new;

	printf("debug -> init cone\n");
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
	if (!str_is_double(args[3]))
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

	printf("debug -> init tore\n");
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
	if (!str_is_double(args[3]) || !str_is_double(args[4]))
		return (1);
	new->scal = ft_atod(args[3]);
	new->scal2 = ft_atod(args[4]);
	if (str_to_colors(&new->color, args[5]))
		return (1);
	return (0);
}

int	init_triangle(char **args, t_env *rt)
{
	t_obj	*new;

	printf("debug -> init triangle\n");
	if (count_arg(args) != 5)
		return (1);
	new = create_object(rt);
	if (!new)
		return (1);
	new->type = OT_TRIANGLE;
	if (str_to_vec3(&new->pt, args[1]))
		return (1);
	if (str_to_vec3(&new->pt2, args[2]))
		return (1);
	if (str_to_vec3(&new->pt3, args[3]))
		return (1);
	if (str_to_colors(&new->color, args[4]))
		return (1);
	return (0);
}

int	init_boloid(char **args, t_env *rt, t_objtype type)
{
	t_obj	*new;

	printf("debug -> init boloid\n");
	if (count_arg(args) != 5)
		return (printf("92"), 1);
	new = create_object(rt);
	if (!new)
		return (printf("95"), 1);
	new->type = type;
	if (str_to_vec3(&new->pt, args[1]))
		return (printf("98"), 1);
	if (str_to_vec3(&new->n, args[2]) || check_norm(new->n))
		return (printf("100"), 1);
	if (!str_is_double(args[3]))
		return (1);
	new->scal = ft_atod(args[3]);
	if (str_to_colors(&new->color, args[4]))
		return (printf("103"), 1);
	return (0);
}

int	init_moebius(char **args, t_env *rt)
{
	t_obj	*new;

	printf("debug -> init moebius\n");
	if (count_arg(args) != 6)
		return (printf("113"), 1);
	new = create_object(rt);
	if (!new)
		return (printf("116"), 1);
	new->type = OT_MOEB;
	if (str_to_vec3(&new->pt, args[1]))
		return (printf("119"), 1);
	if (!str_is_double(args[2]) || !str_is_double(args[3]))
		return (printf("121"), 1);
	new->scal = ft_atod(args[2]);
	new->scal2 = ft_atod(args[3]);
	if (str_to_vec3(&new->n, args[4]) || check_norm(new->n))
		return (printf("125"), 1);
	if (str_to_colors(&new->color, args[5]))
		return (printf("127"), 1);
	return (0);
}
