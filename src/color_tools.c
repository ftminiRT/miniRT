/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:32 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/27 11:38:26 by tbeauman         ###   ########.fr       */
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

t_color color_multiply(t_color c1, t_color c2)
{
    t_color result;
    result.r = (c1.r / 255.0) * (c2.r / 255.0) * 255.0;
    result.g = (c1.g / 255.0) * (c2.g / 255.0) * 255.0;
    result.b = (c1.b / 255.0) * (c2.b / 255.0) * 255.0;
    return result;
}

t_color color_clamp(t_color color)
{
    t_color result;
    result.r = fmin(255, fmax(0, color.r));
    result.g = fmin(255, fmax(0, color.g));
    result.b = fmin(255, fmax(0, color.b));
    return result;
}
