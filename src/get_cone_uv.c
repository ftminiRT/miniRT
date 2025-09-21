
#include "minirt.h"

t_vec3 get_cone_radial(t_obj *obj, t_vec3 hit_point)
{
    return (vec3_sub(hit_point,
        vec3_add(vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n)),
        vec3_scalmult(vec3_dot(vec3_sub(hit_point,
        vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))), obj->n), obj->n))));

}

static void	get_cone_body_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	radial;
    t_basis b;
	t_normap	normap;

    radial = get_cone_radial(obj, hit_point);
    b = make_basis(obj->n);
	normap.u = atan2(vec3_dot(radial, b.v), vec3_dot(radial, b.u)) / (2.0 * M_PI) + 0.5;
	normap.v = vec3_dot(vec3_sub(hit_point,
			vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))), obj->n) / obj->scal2;
	if (obj->checkered)
	{
		map[0] = (int)floor(normap.u * 10.0) % 10;
		map[1] = (int)floor(normap.v * 10.0);
		if (map[0] < 0)
			map[0] += 10;
	}
	else
	{
		map[0] = ((int)floor(normap.u * obj->texture_width) % obj->texture_width
				+ obj->texture_width) % obj->texture_width;
		map[1] = ((int)floor(normap.v * obj->texture_height) % obj->texture_height
				+ obj->texture_height) % obj->texture_height;
	}
}

static void get_cone_cap_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
    t_vec3 local = vec3_sub(hit_point, obj->pt);
    if (obj->checkered)
    {
        map[0] = ((int)floor((local.x / obj->scal + 1.0) * 5.0) % 10 + 10) % 10;
        map[1] = ((int)floor((local.z / obj->scal + 1.0) * 5.0) % 10 + 10) % 10;
    }
    else
    {
        map[0] = ((int)floor((local.x / obj->scal + 1.0) * 0.5 * obj->texture_width)
                % obj->texture_width + obj->texture_width) % obj->texture_width;
        map[1] = ((int)floor((local.z / obj->scal + 1.0) * 0.5 * obj->texture_height)
                % obj->texture_height + obj->texture_height) % obj->texture_height;
    }
}

void	get_cone_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	from_center;
	double	h;

	from_center = vec3_sub(hit_point, obj->pt);
	h = vec3_dot(from_center, obj->n);
	if (h >= 0 && h <= obj->scal2- EPSILON)
		get_cone_body_uv(obj, hit_point, map);
	else
		get_cone_cap_uv(obj, hit_point, map);
}
