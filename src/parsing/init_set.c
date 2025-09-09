/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:36:01 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 13:41:27 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_cam(char **args, t_env *rt)
{
	if (count_arg(args) != 4)
		return (1);
	if (rt->cam.is_set)
		return (1);
	rt->cam.is_set = 1;
	if (str_to_vec3(&rt->cam.pos, args[1]))
		return (1);
	if (str_to_vec3(&rt->cam.dir, args[2]))
		return (1);
	if (check_norm(rt->cam.dir))
		return (1);
	rt->cam.fov = (unsigned char)ft_atoi(args[3]);
	if (rt->cam.fov > 180)
		return (1);
	return (0);
}

int	set_new_spotlight(char **args, t_env *rt)
{
	t_light			*new;
	t_light			*current;
	static size_t	index;

	current = &rt->spot;
	new = ft_calloc(1, sizeof(t_light));
	if (!new)
		return (1);
	while (current->next)
		current = current->next;
	current->next = new;
	if (str_to_vec3(&new->pos, args[1]))
		return (1);
	new->brightness = ft_atod(args[2]);
	new->index = index + 1;
	index++;
	if (str_to_colors(&new->color, args[3]))
		return (1);
	return (0);
}

int	init_spotlight(char **args, t_env *rt)
{
	if (count_arg(args) != 4)
		return (1);
	if (rt->spot.is_set)
		return (set_new_spotlight(args, rt));
	rt->spot.index = 0;
	rt->spot.is_set = 1;
	if (str_to_vec3(&rt->spot.pos, args[1]))
		return (1);
	rt->spot.brightness = ft_atod(args[2]);
	if (str_to_colors(&rt->spot.color, args[3]))
		return (1);
	rt->nb_spots++;
	return (0);
}

int	init_amblight(char **args, t_env *rt)
{
	if (count_arg(args) != 3)
		return (1);
	if (rt->ambient.is_set)
		return (1);
	rt->ambient.is_set = 1;
	rt->ambient.brightness = ft_atod(args[1]);
	if (check_brightness(rt->ambient.brightness))
		return (1);
	if (str_to_colors(&rt->ambient.color, args[2]))
		return (1);
	rt->ambient.pos.x = 0;
	rt->ambient.pos.y = 0;
	rt->ambient.pos.z = 0;
	return (0);
}
