/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:31:14 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:31:14 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	null_vec(void)
{
	return ((t_vec3){0, 0, 0});
}

t_uipt	btn_sz(void)
{
	return ((t_uipt){26, 26});
}

int	swapd(double *a, double *b)
{
	double	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
	return (1);
}

int	dblsgn(double x)
{
	if (x < -EPSILON)
		return (-1);
	return (x > EPSILON);
}
