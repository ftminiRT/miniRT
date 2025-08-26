/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:32 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/26 15:16:33 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (unsigned char)fmin(255, (int)c1.r + (int)c2.r);
	result.g = (unsigned char)fmin(255, (int)c1.g + (int)c2.g);
	result.b = (unsigned char)fmin(255, (int)c1.b + (int)c2.b);
	return (result);
}

t_color	color_scale(t_color c, double factor)
{
	t_color	result;

	result.r = (unsigned char)fmin(255, (int)(c.r * factor));
	result.g = (unsigned char)fmin(255, (int)(c.g * factor));
	result.b = (unsigned char)fmin(255, (int)(c.b * factor));
	return (result);
}

t_color	calc_ambient(t_color base, t_color amb, double bright)
{
	t_color	ambient;
	t_color	amb_scaled;

	amb_scaled = color_scale(amb, bright);
	ambient.r = (unsigned char)((base.r * amb_scaled.r) / 255);
	ambient.g = (unsigned char)((base.g * amb_scaled.g) / 255);
	ambient.b = (unsigned char)((base.b * amb_scaled.b) / 255);
	return (ambient);
}
