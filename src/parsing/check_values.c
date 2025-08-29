/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-29 13:12:22 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-08-29 13:12:22 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_brightness(double b)
{
	return (b < 0.0 || b > 1.0);
}

int	check_norm(t_vec3 n)
{
	int	c;

	c = 1;
	if (n.x < -1.0 || n.x > 1.0 || \
		n.y < -1.0 || n.y > 1.0 || \
		n.z < -1.0 || n.z > 1.0)
		return (1);
	if (n.x || n.y || n.z)
		c--;
	return (c);
}

int	count_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	check_angle(double ang)
{
	if (ang < 0 || ang > 360)
		return (1);
	return (0);
}
