/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_compute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:26 by tbeauman          #+#    #+#             */
/*   Updated: 2025/09/05 07:48:38 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static t_color	multi_spotlights(t_env *rt, t_obj *obj, t_vec3 hit_point,
		t_ray ray)
{
	t_phong	phong;
	t_light	*cur_spot;
	t_color	ret;

	ret = (t_color){0, 0, 0};
	phong.normal = rt->get_norm[obj->type](obj, hit_point);
	if (vec3_dot(ray.dir, phong.normal) > 0)
		phong.normal = vec3_scalmult(-1, phong.normal);
	phong.view = vec3_scalmult(-1.0, ray.dir);
	vec3_normalize(&phong.view);
	cur_spot = &rt->spot;
	while (cur_spot)
	{
		if (!in_shadow(rt, cur_spot, hit_point))
		{
			phong.light = vec3_sub(cur_spot->pos, hit_point);
			vec3_normalize(&phong.light);
			phong.diffuse = compute_diffuse(phong, obj, cur_spot);
			phong.specular = compute_specular(phong, obj, cur_spot);
			ret = color_add(ret, phong.diffuse);
			ret = color_add(ret, phong.specular);
		}
		cur_spot = cur_spot->next;
	}
	return (ret);
}

t_color	get_texture_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	int				map[2];
	unsigned char	*data;
	int				offset;
	t_color			color;

	(void)rt;
	rt->get_uv[obj->type](obj, hit_point, map);
	map[0] = (map[0] % obj->texture_width + obj->texture_width)
		% obj->texture_width;
	map[1] = (map[1] % obj->texture_height + obj->texture_height)
		% obj->texture_height;
	if (obj->type == OT_PLANE)
		map[1] = obj->texture_height - 1 - map[1];
	data = (unsigned char *)obj->texture_data;
	offset = map[1] * obj->texture_size_line + map[0] * (obj->texture_bpp / 8);
	color.r = data[offset + 2];
	color.g = data[offset + 1];
	color.b = data[offset + 0];
	return (color);
}

t_color	get_color(t_env *rt, t_obj *obj, t_vec3 hit_point, const t_ray ray)
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
	return (color_add(ret, multi_spotlights(rt, obj, hit_point, ray)));
}
