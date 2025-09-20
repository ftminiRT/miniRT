/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_values_co.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 16:14:02 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 16:14:02 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_values_co(void *rt, t_uipane *cur)
{
	t_obj	*o;

	o = cur->obj;
	putnbr_ui((t_env *)rt, 157, 92, o->color.r);
	putnbr_ui((t_env *)rt, 157, 122, o->color.g);
	putnbr_ui((t_env *)rt, 157, 152, o->color.b);
	putnbr_ui((t_env *)rt, 157, 182, o->pt.x);
	putnbr_ui((t_env *)rt, 157, 212, o->pt.y);
	putnbr_ui((t_env *)rt, 157, 242, o->pt.z);
	putnbr_ui((t_env *)rt, 157, 272, o->n.x);
	putnbr_ui((t_env *)rt, 157, 302, o->n.y);
	putnbr_ui((t_env *)rt, 157, 332, o->n.z);
	putnbr_ui((t_env *)rt, 157, 362, o->scal);
	putnbr_ui((t_env *)rt, 157, 392, o->shine);
	putnbr_ui((t_env *)rt, 157, 422, o->reflect);
	return (0);
}
