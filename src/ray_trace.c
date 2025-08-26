/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:48 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/26 18:52:51 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*compute_intersections(t_env *rt, t_ray *ray)
{
	t_obj	*objs;
	double	closest_t;
	double	t;
	t_obj	*closest;

	closest_t = INFINITY;
	t = INFINITY;
	closest = NULL;
	objs = rt->objects;
	while (objs)
	{
		t = rt->hit_object[objs->type](ray, objs);
		if (0 < t && t < closest_t)
		{
			closest_t = t;
			closest = objs;
		}
		objs = objs->next;
	}
	if (closest)
		ray->hit = closest_t;
	return (closest);
}

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

void	normalize_objs_normal(t_env *rt)
{
	t_obj	*objs;

	objs = rt->objects;
	while (objs)
	{
		objs->shine = 1;
		if (objs->type == OT_PLANE)
			vec3_normalize(&objs->n);
		if (objs->type == OT_CYL)
			vec3_normalize(&objs->n);
		objs = objs->next;
	}
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

t_color	get_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	t_vec3	normal;
	t_vec3	light;
	t_vec3	view;
	t_vec3	reflected;
	double	ambient;
	double	diffuse;
	double	specular;
	double	intensity;

	normal = get_normal(obj, hit_point);
	light = vec3_sub(rt->spot.pos, hit_point);
	vec3_normalize(&light);
	view = vec3_sub(rt->ray.pt, hit_point);
	vec3_normalize(&view);
	reflected = vec3_sub(
		vec3_scalmult(2.0 * fabs(vec3_dot(normal, light)), normal),
		 light);
	vec3_normalize(&reflected);
	ambient = rt->ambient.brightness;

	if (obj->type == OT_PLANE)
		diffuse = rt->spot.brightness * fabs(vec3_dot(light, normal));
	else
		diffuse = rt->spot.brightness * fmax(0.0, vec3_dot(light, normal));

	specular = 0.0;
	if (vec3_dot(normal, light) > 0.0)
		specular = rt->spot.brightness *
			pow(fmax(0.0, vec3_dot(reflected, view)), obj->shine);

	intensity = ambient + diffuse + specular;

	t_color	ret;

    ret.r = fmin(255, fmax(0, obj->color.r * intensity));
    ret.g = fmin(255, fmax(0, obj->color.g * intensity));
    ret.b = fmin(255, fmax(0, obj->color.b * intensity));
	return (ret);
}

void	ray_trace(t_env *rt)
{
	t_obj	*hitted;
	int		i;
	int		j;
	t_vec3	hit_point;
	t_color	color;

	normalize_objs_normal(rt);
	hitted = NULL;
	rt->ray.pt = rt->cam.pos;
	vec3_normalize(&rt->cam.dir);
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			rt->ray.pt = rt->cam.pos;
			rt->ray.dir = compute_ray_dir(rt, i, j);
			rt->ray.hit = INFINITY;
			hitted = compute_intersections(rt, &rt->ray);
			if (hitted)
			{
				hit_point = vec3_add(rt->ray.pt, vec3_scalmult(rt->ray.hit, rt->ray.dir));
				color = get_color(rt, hitted, hit_point);
				putpixel(i, j, rt, color);
				// putpixel(i, j, rt, blinn_phong(rt, hitted, hit_point));
			}
			else
				putpixel(i, j, rt, (t_color){0, 0, 0});
		}
	}
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.img.img, 0, 0);
}
