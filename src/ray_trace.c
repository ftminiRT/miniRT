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

// void	ray_trace(t_env *rt)
// {
// 	t_obj	*hitted;
// 	int		i;
// 	int		j;

// 	init_rt(rt);
// 	hitted = NULL;
// 	j = -1;
// 	while (++j < HEIGHT)
// 	{
// 		i = -1;
// 		while (++i < WIDTH)
// 		{
// 			compute_ray(rt, &rt->ray, i, j);
// 			hitted = compute_intersections(rt, &rt->ray);
// 			if (hitted)
// 				putpixel(i, j, rt, get_color(rt, hitted, vec3_add(rt->ray.pt,
// 								vec3_scalmult(rt->ray.hit, rt->ray.dir))));
// 			else
// 				putpixel(i, j, rt, (t_color){0, 0, 0});
// 		}
// 	}
// 	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.img.img, 0, 0);
// }
#define MAX_DEPTH 10

// Fonction de réflexion
t_vec3 reflect(t_vec3 I, t_vec3 N)
{
    double dot = vec3_dot(I, N);
    return vec3_sub(I, vec3_scalmult(2 * dot, N));
}

// Fonction récursive de ray tracing
t_color trace_ray(t_env *rt, t_ray ray, int depth)
{
    t_obj   *hitted;
    t_color local_color;
    t_color reflected_color;
    t_vec3  hit_point, N, R;

    if (depth > MAX_DEPTH)
        return ((t_color){0, 0, 0});

    hitted = compute_intersections(rt, &ray);
    if (!hitted)
        return ((t_color){0, 0, 0});

    // Calcul du point d'impact
    hit_point = vec3_add(ray.pt, vec3_scalmult(ray.hit, ray.dir));

    // Couleur locale (texture / normal map / shading)
    local_color = get_color(rt, hitted, hit_point, ray);

    // Réflexion
    if (hitted->reflect > 0.0)
    {
        N = rt->get_norm[hitted->type](hitted, hit_point); // Normale au point d'impact
        R = reflect(ray.dir, N);
        vec3_normalize(&R);

        // Décalage pour éviter self-intersection
        hit_point = vec3_add(hit_point, vec3_scalmult(EPSILON, N));

        t_ray reflected_ray = (t_ray){hit_point, R, 0, (t_color){0, 0, 0}};
        reflected_color = trace_ray(rt, reflected_ray, depth + 1);

        // Mélange couleur locale et réfléchie
        local_color.r = (1 - hitted->reflect) * local_color.r + hitted->reflect * reflected_color.r;
        local_color.g = (1 - hitted->reflect) * local_color.g + hitted->reflect * reflected_color.g;
        local_color.b = (1 - hitted->reflect) * local_color.b + hitted->reflect * reflected_color.b;
    }

    return local_color;
}

// Version complète de ray_trace pour l'image
void ray_trace(t_env *rt)
{
    int i, j;

    init_rt(rt);

    for (j = 0; j < HEIGHT; j++)
    {
        for (i = 0; i < WIDTH; i++)
        {
            compute_ray(rt, &rt->ray, i, j);

            t_color color = trace_ray(rt, rt->ray, 0);

            putpixel(i, j, rt, color);
        }
    }

    mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.img.img, 0, 0);
}
