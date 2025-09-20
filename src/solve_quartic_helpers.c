/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:53:26 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:53:26 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_k1_v2(t_quartic *q)
{
	if (q->v1 == q->v[0])
	{
		q->k1 = 0;
		q->v2 = fmax(q->v[1], q->v[2]);
	}
	else if (q->v1 == q->v[1])
	{
		q->k1 = 1;
		q->v2 = fmax(q->v[0], q->v[2]);
	}
	else
	{
		q->k1 = 2;
		q->v2 = fmax(q->v[0], q->v[1]);
	}
}

static void	set_k2(t_quartic *q)
{
	if (q->v2 == q->v[0])
		q->k2 = 0;
	else if (q->v2 == q->v[1])
		q->k2 = 1;
	else
		q->k2 = 2;
}

static void	set_w(double u, double *wr, double *wi)
{
	if (u >= 0.0)
	{
		*wr = sqrt(u);
		*wi = 0.0;
	}
	else
	{
		*wr = 0.0;
		*wi = sqrt(-u);
	}
}

void	deal_with_pos_disc(t_quartic *q)
{
	q->mt = 2;
	set_d3(q->v, fabs(q->u[0]), fabs(q->u[1]), fabs(q->u[2]));
	q->v1 = fmax(fmax(q->v[0], q->v[1]), q->v[2]);
	set_k1_v2(q);
	set_k2(q);
	set_w(q->u[q->k1], &q->w1r, &q->w1i);
	set_w(q->u[q->k2], &q->w2r, &q->w2i);
}
