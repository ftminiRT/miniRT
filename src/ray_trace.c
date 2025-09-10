
#include "minirt.h"

t_vec3	compute_ray_dir(t_env *rt, int i, int j)
{
	t_vec3	ret;
	double	fov_xrad;
	double	fov_yrad;
	double	px;
	double	py;

	fov_xrad = rt->cam.fov * M_PI / 180.0;
	fov_yrad = 2 * atan(tan(fov_xrad / 2) / ((double)WIDTH / (double)HEIGHT));
	px = (2 * ((i + 0.5) / (double)WIDTH) - 1) * tan(fov_xrad / 2)
		* ((double)WIDTH / (double)HEIGHT);
	py = (1 - 2 * ((j + 0.5) / (double)HEIGHT)) * tan(fov_yrad / 2);
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

t_vec3	reflect(t_vec3 I, t_vec3 N)
{
	double	dot;

	dot = vec3_dot(I, N);
	return (vec3_normalized(vec3_sub(I, vec3_scalmult(2 * dot, N))));
}

t_color	trace_ray(t_env *rt, t_ray ray, int depth)
{
	t_reflect_data	d;

	if (depth > MAX_DEPTH)
		return ((t_color){0, 0, 0});
	d.hitted = compute_intersections(rt, &ray);
	if (!d.hitted)
		return ((t_color){0, 0, 0});
	d.hit_point = vec3_add(ray.pt, vec3_scalmult(ray.hit, ray.dir));
	d.local_color = get_color(rt, d.hitted, d.hit_point, ray);
	if (d.hitted->reflect > 0.0)
	{
		d.normal = rt->get_norm[d.hitted->type](d.hitted, d.hit_point);
		d.reflected = reflect(ray.dir, d.normal);
		d.hit_point = vec3_add(d.hit_point, vec3_scalmult(EPSILON, d.normal));
		d.reflected_ray = (t_ray){d.hit_point, d.reflected, 0, (t_color){0, 0,
			0}};
		d.reflected_color = trace_ray(rt, d.reflected_ray, depth + 1);
		d.local_color.r = (1 - d.hitted->reflect) * d.local_color.r
			+ d.hitted->reflect * d.reflected_color.r;
		d.local_color.g = (1 - d.hitted->reflect) * d.local_color.g
			+ d.hitted->reflect * d.reflected_color.g;
		d.local_color.b = (1 - d.hitted->reflect) * d.local_color.b
			+ d.hitted->reflect * d.reflected_color.b;
	}
	return (d.local_color);
}

void	ray_trace(t_env *rt)
{
	int		i;
	int		j;
	t_color	color;

	init_rt(rt);
	debug_print_set(rt);
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			compute_ray(rt, &rt->ray, i, j);
			color = trace_ray(rt, rt->ray, 0);
			putpixel(i, j, rt, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.img.img, 0, 0);
}
