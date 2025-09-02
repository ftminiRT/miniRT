/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:48 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 19:30:23 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	camera_transform(t_vec3 dir_local, t_vec3 cam_dir)
{
	t_vec3	forward;
	t_vec3	up_ref;
	t_vec3	right;
	t_vec3	up;
	t_vec3	world_dir;

	forward = cam_dir;
	vec3_normalize(&forward);
	if (fabs(forward.y) > 0.99)
		up_ref = (t_vec3){0, 0, 1};
	else
		up_ref = (t_vec3){0, 1, 0};
	right = vec3_cross(forward, up_ref);
	vec3_normalize(&right);
	up = vec3_cross(right, forward);
	vec3_normalize(&up);
	world_dir.x = dir_local.x * right.x + dir_local.y * up.x + dir_local.z
		* forward.x;
	world_dir.y = dir_local.x * right.y + dir_local.y * up.y + dir_local.z
		* forward.y;
	world_dir.z = dir_local.x * right.z + dir_local.y * up.z + dir_local.z
		* forward.z;
	return (world_dir);
}

t_vec3	compute_ray_dir(t_env *rt, int i, int j)
{
	t_vec3	ret;
	double	fov_rad;
	double	px;
	double	py;

	fov_rad = rt->cam.fov * M_PI / 180.0;
	px = (2 * ((i + 0.5) / (double)WIDTH) - 1) * tan(fov_rad / 2)
		* ((double)WIDTH / (double)HEIGHT);
	py = (1 - 2 * ((j + 0.5) / (double)HEIGHT)) * tan(fov_rad / 2);
	ret = camera_transform((t_vec3){px, py, 1}, rt->cam.dir);
	vec3_normalize(&ret);
	return (ret);
}

void	compute_ray(t_env *rt, t_ray *ray, int i, int j)
{
	ray->pt = rt->cam.pos;
	ray->dir = compute_ray_dir(rt, i, j);
	ray->hit = INFINITY;
}

void	ray_trace(t_env *rt)
{
	t_obj	*hitted;
	t_vec3	hit_point;
	int		i;
	int		j;

	init_rt(rt);
	hitted = NULL;
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			compute_ray(rt, &rt->ray, i, j);
			hitted = compute_intersections(rt, &rt->ray);
			if (hitted)
			{
				hit_point = vec3_add(rt->ray.pt,
								vec3_scalmult(rt->ray.hit, rt->ray.dir));
				if (!hitted->checkered)
					putpixel(i, j, rt, get_color(rt, hitted, hit_point));
				else if (hitted->checkered)
					putpixel(i, j, rt, get_checkered_color(rt, hitted, hit_point));
			}
			else
				putpixel(i, j, rt, (t_color){0, 0, 0});
		}
	}
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.img.img, 0, 0);
}
