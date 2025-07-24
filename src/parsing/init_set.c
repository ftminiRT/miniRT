/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:36:01 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 19:25:37 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_cam(char **args, t_env *rt)
{
	str_to_vec3(&rt->cam.pos, args[1]);
	str_to_vec3(&rt->cam.dir, args[2]);
	rt->cam.fov = (unsigned char)ft_atoi(args[3]);
	return (0);
}

int	init_spotlight(char **args, t_env *rt)
{
	str_to_vec3(&rt->spot.pos, args[1]);
	rt->spot.brightness = ft_atod(args[2]);
	str_to_colors(&rt->spot.color, args[3]);
	return (0);
}

int	init_amblight(char **args, t_env *rt)
{
	rt->ambient.brightness = ft_atod(args[1]);
	str_to_colors(&rt->ambient.color, args[2]);
	rt->ambient.pos.x = 0;
	rt->ambient.pos.y = 0;
	rt->ambient.pos.z = 0;
	return (0);
}
