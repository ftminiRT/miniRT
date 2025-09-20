/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:42:50 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:42:50 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_hit_fcts(t_env *rt)
{
	rt->hit_object[OT_PLANE] = hit_plane;
	rt->hit_object[OT_SPHERE] = hit_sphere;
	rt->hit_object[OT_CYL] = hit_cylinder;
	rt->hit_object[OT_TORE] = hit_torus;
	rt->hit_object[OT_RING] = hit_ring;
	rt->hit_object[OT_CONE] = hit_cone;
	rt->hit_object[OT_MOEB] = hit_moebius;
}

static void	init_normal_fcts(t_env *rt)
{
	rt->get_norm[OT_PLANE] = plane_normal;
	rt->get_norm[OT_SPHERE] = sphere_normal;
	rt->get_norm[OT_CYL] = cylinder_normal;
	rt->get_norm[OT_TORE] = torus_normal;
	rt->get_norm[OT_RING] = ring_normal;
	rt->get_norm[OT_CONE] = cone_normal;
	rt->get_norm[OT_MOEB] = moebius_normal;
}

static void	init_uv_fcts(t_env *rt)
{
	rt->get_uv[OT_PLANE] = get_plane_uv;
	rt->get_uv[OT_SPHERE] = get_sphere_uv;
	rt->get_uv[OT_CYL] = get_cylinder_uv;
	rt->get_uv[OT_TORE] = get_torus_uv;
	rt->get_uv[OT_RING] = get_ring_uv;
	rt->get_uv[OT_MOEB] = get_moebius_uv;
}

void	env_init(t_env *rt)
{
	init_hit_fcts(rt);
	init_normal_fcts(rt);
	init_uv_fcts(rt);
	rt->cam.is_set = 0;
	rt->ambient.is_set = 0;
	rt->spot.is_set = 0;
	rt->spot.next = NULL;
	rt->selected.type = CAM;
	rt->selected.cam = &rt->cam;
	rt->selected.spot = &rt->spot;
	rt->selected.amb = &rt->ambient;
	rt->selected.obj = NULL;
	rt->ui.dft_itms = 0;
	rt->nb_spots = 0;
	rt->render = false;
}
