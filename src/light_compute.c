/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_compute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:26 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/03 07:45:19 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	in_shadow(t_env *rt, t_light *spot, t_vec3 hit_point)
{
	t_ray	light_ray;
	t_ray	og_ray;
	t_obj	*hit;
	double	light_dist;

	light_ray.dir = vec3_sub(spot->pos, hit_point);
	light_dist = vec3_norm(light_ray.dir);
	vec3_normalize(&light_ray.dir);
	light_ray.pt = vec3_add(hit_point, vec3_scalmult(EPSILON, light_ray.dir));
	og_ray = rt->ray;
	rt->ray = light_ray;
	hit = compute_intersections(rt, &light_ray);
	if (hit && (light_ray.hit > EPSILON && light_ray.hit < light_dist))
	{
		rt->ray = og_ray;
		return (true);
	}
	rt->ray = og_ray;
	return (false);
}

static t_color	compute_diffuse(t_phong phong, t_obj *obj, t_light *cur_spot)
{
	double	diff_factor;
	t_color	diffuse;

	if (obj->type == OT_PLANE)
		diff_factor = cur_spot->brightness * fabs(vec3_dot(phong.light,
					phong.normal));
	else
		diff_factor = cur_spot->brightness * fmax(0.0, vec3_dot(phong.light,
					phong.normal));
	diffuse = color_scale(color_multiply(cur_spot->color, obj->t_color),
			diff_factor * cur_spot->brightness);
	return (diffuse);
}

static t_color	compute_specular(t_phong phong, t_obj *obj, t_light *cur_spot)
{
	double	spec_factor;
	t_color	specular;

	phong.reflected = vec3_sub(vec3_scalmult(2.0 * fabs(vec3_dot(phong.normal,
						phong.light)), phong.normal), phong.light);
	vec3_normalize(&phong.reflected);
	spec_factor = 0.0;
	vec3_normalize(&phong.reflected);
	if (vec3_dot(phong.normal, phong.light) > 0.0)
		spec_factor = cur_spot->brightness * pow(fmax(0.0,
					vec3_dot(phong.reflected, phong.view)), obj->shine);
	specular = color_scale(cur_spot->color, spec_factor * cur_spot->brightness);
	return (specular);
}

static void	multi_spotlights(t_env *rt, t_obj *obj, t_vec3 hit_point,
		t_color *ret)
{
	t_phong	phong;
	t_color	diffuse;
	t_color	specular;
	t_light	*cur_spot;

	phong.normal = rt->get_norm[obj->type](obj, hit_point);
	if (vec3_dot(rt->ray.dir, phong.normal) > 0)
		phong.normal = vec3_scalmult(-1, phong.normal);
	phong.view = vec3_sub(rt->ray.pt, hit_point);
	vec3_normalize(&phong.view);
	cur_spot = &rt->spot;
	while (cur_spot)
	{
		if (!in_shadow(rt, cur_spot, hit_point))
		{
			phong.light = vec3_sub(cur_spot->pos, hit_point);
			vec3_normalize(&phong.light);
			diffuse = compute_diffuse(phong, obj, cur_spot);
			specular = compute_specular(phong, obj, cur_spot);
			*ret = color_add(*ret, diffuse);
			*ret = color_add(*ret, specular);
		}
		cur_spot = cur_spot->next;
	}
}
t_color get_texture_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
    int map[2];
    unsigned char *data;
    int offset;
    t_color color;

	(void)rt;
    // Calculer UV selon type d'objet
    if (obj->type == OT_PLANE)
        get_plane_uv(obj, hit_point, map);
    else if (obj->type == OT_SPHERE)
        get_sphere_uv(obj, hit_point, map);
    else if (obj->type == OT_CYL)
        get_cylinder_uv(obj, hit_point, map);
	else if (obj->type == OT_TORE)
		get_torus_uv(obj, hit_point, map);
	else if (obj->type == OT_MOEB)
		get_moebius_uv(obj, hit_point, map);
	else
        return (obj->color);
    // Wrap UV
    map[0] = (map[0] % obj->texture_width + obj->texture_width) % obj->texture_width;
    map[1] = (map[1] % obj->texture_height + obj->texture_height) % obj->texture_height;
	if (obj->type == OT_PLANE)
		map[1] = obj->texture_height - 1 - map[1];

    // Pointer sur la mémoire de la texture
    data = (unsigned char *)obj->texture_data;
    offset = map[1] * obj->texture_size_line + map[0] * (obj->texture_bpp / 8);

    // Lire chaque canal
    color.r = data[offset + 2]; // Rouge
    color.g = data[offset + 1]; // Vert
    color.b = data[offset + 0]; // Bleu

    return (color);
}

t_color	get_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	t_color	ambient;
	t_color	ret;
	t_color	base_color;

	if (obj->checkered)
		base_color = get_checkered_color(rt, obj, hit_point);
	else if (obj->texture_data)
		base_color = get_texture_color(rt, obj, hit_point);
	else
		base_color = obj->color;
	obj->t_color = base_color;
	ambient = color_scale(color_multiply(rt->ambient.color, base_color),
			rt->ambient.brightness);
	ret = ambient;
	multi_spotlights(rt, obj, hit_point, &ret);
	return (ret);
}
