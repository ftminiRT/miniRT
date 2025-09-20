/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:28:18 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:28:18 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	deal_with_neg_disc(t_quartic *q)
{
	q->mt = 3;
	if (0.0 == q->u[1] && 0.0 == q->u[2])
		q->arg = 0.0;
	else
		q->arg = sqrt(sqrt(q->u[1] * q->u[1] + q->u[2] * q->u[2]));
	q->theta = atan2(q->u[2], q->u[1]);
	q->w1r = q->arg * cos(q->theta / 2.0);
	q->w1i = q->arg * sin(q->theta / 2.0);
	q->w2r = q->w1r;
	q->w2i = -q->w1i;
}

static void	fill_zarr(t_quartic *q, double *a)
{
	q->w3r = q->qq / 8.0 * (q->w1i * q->w2i - q->w1r * q->w2r) / (q->w1i
			* q->w1i + q->w1r * q->w1r) / (q->w2i * q->w2i + q->w2r * q->w2r);
	q->h = a[3] / 4.0;
	q->zarr[0] = q->w1r + q->w2r + q->w3r - q->h;
	q->zarr[1] = -q->w1r - q->w2r + q->w3r - q->h;
	q->zarr[2] = -q->w1r + q->w2r - q->w3r - q->h;
	q->zarr[3] = q->w1r - q->w2r - q->w3r - q->h;
}

static int	deal_with_it(t_quartic *q, double *a, double *r)
{
	init_quartic_solver(q, a);
	find_solution_to_resolvent_cubic(q);
	if (0.0 == q->disc)
		q->u[2] = q->u[1];
	if (0 >= q->disc)
		deal_with_pos_disc(q);
	else
		deal_with_neg_disc(q);
	fill_zarr(q, a);
	if (2 == q->mt)
	{
		if (q->u[q->k1] >= 0 && q->u[q->k2] >= 0)
		{
			q->mt = 1;
			handle_r_and_zarr(r, q->zarr);
		}
		else
			return (0);
	}
	else
		set_d3(r, q->zarr[0], q->zarr[1], -1);
	return (1);
}

static void	order_roots(double *r)
{
	if (r[0] > r[1])
		swapd(&r[0], &r[1]);
	if (r[0] > r[2])
		swapd(&r[0], &r[2]);
	if (r[0] > r[3])
		swapd(&r[0], &r[3]);
	if (r[1] > r[2])
		swapd(&r[1], &r[2]);
	if (r[2] > r[3])
	{
		swapd(&r[2], &r[3]);
		if (r[1] > r[2])
			swapd(&r[1], &r[2]);
	}
}

int	solve_quartic(double *a, double *r)
{
	t_quartic	q;

	if (a[2] == 0.0 && a[1] == 0.0 && (a[0] == 0.0 || a[3] == 0.0))
		return (deal_with_degenerate(a, r));
	if (a[1] == 0.0 && a[0] == 0.0)
	{
		r[0] = 0.0;
		r[1] = 0.0;
		set_d3(q.args, a[2], a[3], 1);
		if (solve_quadratic(q.args, &r[2]) == 0)
			q.mt = 3;
		else
			q.mt = 1;
	}
	else if (!deal_with_it(&q, a, r))
		return (0);
	if (q.mt == 1)
	{
		order_roots(r);
		return (4);
	}
	if (r[0] > r[1])
		swapd(&r[0], &r[1]);
	return (2);
}
