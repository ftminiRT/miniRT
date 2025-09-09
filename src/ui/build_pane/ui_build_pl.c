/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_build_pl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 15:19:25 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-04 15:19:25 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_pane_pl(void *rt, t_uipane *current)
{
	t_obj	*o;
	t_basis	b;

	build_local_basis(rt, &b);
	o = current->obj;
	o->local_basis = b;
	if (build_pane_color(rt, current))
		return (1);
	if (build_pane_pos(rt, current, &o->pt, 182))
		return (1);
	if (build_pane_dir(rt, current, &o->n, 272))
		return (1);
	if (build_pane_mat(rt, current, 362))
		return (1);
	return (0);
}
