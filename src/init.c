/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:48:44 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/05 08:10:23 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_quartic_solver(t_quartic *q, double *a)
{
	q->aa = a[3] * a[3];
	q->pp = a[2] - (3.0 / 8.0) * q->aa;
	q->qq = a[1] - (1.0 / 2.0) * a[3] * (a[2] - (1.0 / 4.0) * q->aa);
	q->rr = a[0] - (1.0 / 4.0) * (a[3] * a[1] - (1.0 / 4.0) * q->aa * (a[2]
				- (3.0 / 16.0) * q->aa));
	q->rc = (1.0 / 2.0) * q->pp;
	q->sc = (1.0 / 4.0) * ((1.0 / 4.0) * q->pp * q->pp - q->rr);
	q->tc = -((1.0 / 8.0) * q->qq * (1.0 / 8.0) * q->qq);
	q->qcub = (q->rc * q->rc - 3 * q->sc);
	q->rcub = (2 * q->rc * q->rc * q->rc - 9 * q->rc * q->sc + 27 * q->tc);
	q->bq = q->qcub / 9;
	q->br = q->rcub / 54;
	q->bq3 = q->bq * q->bq * q->bq;
	q->br2 = q->br * q->br;
	q->cr2 = 729 * q->rcub * q->rcub;
	q->cq3 = 2916 * q->qcub * q->qcub * q->qcub;
	q->disc = (q->cr2 - q->cq3) / 2125764.0;
	q->w1r = 0.0;
	q->w1i = 0.0;
	q->w2r = 0.0;
	q->w2i = 0.0;
}

void	init_base(t_obj *obj, t_basis *b)
{
	b->w = vec3_normalized(obj->n);
	if (fabs(b->w.y) < 0.9)
		b->u = vec3_normalized(vec3_cross((t_vec3){0, 1, 0}, b->w));
	else
		b->u = vec3_normalized(vec3_cross((t_vec3){1, 0, 0}, b->w));
	b->v = vec3_cross(b->w, b->u);
}

void	rt_mlx_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		error_exit("connection to mlx error");
	mlx->win = mlx_new_window(mlx->mlx, WIDTH + UI_WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		error_exit("window error");
	mlx->img.img = init_img(mlx, &mlx->img, WIDTH, HEIGHT);
	mlx->ui.img = init_img(mlx, &mlx->ui, UI_WIDTH, UI_HEIGHT);
}

void	init_rt(t_env *rt)
{
	normalize_objs(rt);
	if (rt->ambient.brightness < 0)
		rt->ambient.brightness = 0;
	if (rt->ambient.brightness > 1)
		rt->ambient.brightness = 1;
	vec3_normalize(&rt->cam.dir);
	rt->ray.pt = rt->cam.pos;
}

void	normalize_objs(t_env *rt)
{
	t_obj	*objs;

	objs = rt->objects;
	while (objs)
	{
		if (objs->shine <= 0)
			objs->shine = 1;
		if (objs->type == OT_PLANE || objs->type == OT_CYL
			|| objs->type == OT_MOEB || objs->type == OT_TORE
			|| objs->type == OT_RING)
			vec3_normalize(&objs->n);
		if (objs->scal < EPSILON)
			objs->scal = 0;
		if (objs->scal2 < EPSILON && (objs->type == OT_TORE
				|| objs->type == OT_RING))
			objs->scal2 = 0;
		if (objs->scal3 < EPSILON && objs->type == OT_RING)
			objs->scal3 = 0;
		objs = objs->next;
	}
}
