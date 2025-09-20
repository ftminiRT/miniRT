/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_values_dft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 16:14:10 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 16:14:10 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_values_dft(void *rt, t_uipane *cur)
{
	t_light	*a;
	t_cam	*c;

	a = cur->light;
	c = cur->cam;
	putnbr_ui((t_env *)rt, 157, 92, a->color.r);
	putnbr_ui((t_env *)rt, 157, 122, a->color.g);
	putnbr_ui((t_env *)rt, 157, 152, a->color.b);
	putnbr_ui((t_env *)rt, 157, 182, a->brightness);
	putnbr_ui((t_env *)rt, 157, 242, c->pos.x);
	putnbr_ui((t_env *)rt, 157, 272, c->pos.y);
	putnbr_ui((t_env *)rt, 157, 302, c->pos.z);
	putnbr_ui((t_env *)rt, 157, 332, c->dir.x);
	putnbr_ui((t_env *)rt, 157, 362, c->dir.y);
	putnbr_ui((t_env *)rt, 157, 392, c->fov);
	return (0);
}
