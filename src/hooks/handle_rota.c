/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rota.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 16:17:59 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 16:17:59 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rot_cam(int kc, t_env *rt, double step)
{
	if (kc == KEY_J)
		rotate_selected(rt, (t_vec3){0, -step, 0});
	if (kc == KEY_L)
		rotate_selected(rt, (t_vec3){0, step, 0});
	if (kc == KEY_K)
		rotate_selected(rt, (t_vec3){0, 0, -step});
	if (kc == KEY_I)
		rotate_selected(rt, (t_vec3){0, 0, step});
}

void	rot_obj(int kc, t_env *rt, double step)
{
	if (kc == KEY_J)
		rotate_selected(rt, (t_vec3){0, -step, 0});
	if (kc == KEY_L)
		rotate_selected(rt, (t_vec3){0, step, 0});
	if (kc == KEY_K)
		rotate_selected(rt, (t_vec3){-step, 0, 0});
	if (kc == KEY_I)
		rotate_selected(rt, (t_vec3){step, 0, 0});
	if (kc == KEY_U)
		rotate_selected(rt, (t_vec3){0, 0, -step});
	if (kc == KEY_O)
		rotate_selected(rt, (t_vec3){0, 0, step});
}
