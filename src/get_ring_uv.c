#include "minirt.h"

static void	get_local_axes(t_vec3 n, t_ring_uv *uv)
{
	uv->w_axis = vec3_normalized(n);
	if (fabs(uv->w_axis.y) < 0.9)
		uv->u_axis = vec3_normalized(vec3_cross((t_vec3){0, 1, 0}, uv->w_axis));
	else
		uv->u_axis = vec3_normalized(vec3_cross((t_vec3){1, 0, 0}, uv->w_axis));
	uv->v_axis = vec3_cross(uv->w_axis, uv->u_axis);
}

static double	get_v_angle(t_ring_uv *uv, t_obj *obj)
{
	double	cx;
	double	cz;
	double	ex;
	double	ey;
	double	ez;

	cx = obj->scal2 * cos(uv->theta);
	cz = obj->scal2 * sin(uv->theta);
	ex = (uv->local.x - cx) / obj->scal;
	ey = uv->local.y / obj->scal3;
	ez = (uv->local.z - cz) / obj->scal;
	return (atan2(ey, sqrt(ex * ex + ez * ez)));
}

void	get_ring_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_ring_uv	uv;

	get_local_axes(obj->n, &uv);
	uv.rel = vec3_sub(hit_point, obj->pt);
	uv.local = (t_vec3){vec3_dot(uv.rel, uv.u_axis),
		vec3_dot(uv.rel, uv.w_axis), vec3_dot(uv.rel, uv.v_axis)};
	uv.theta = atan2(uv.local.z, uv.local.x);
	if (uv.theta < 0)
		uv.theta += 2.0 * M_PI;
	uv.u = uv.theta / (2.0 * M_PI);
	uv.phi = get_v_angle(&uv, obj);
	uv.v = (uv.phi / M_PI) + 0.5;
	if (!obj->checkered)
	{
		map[0] = (int)floor(uv.u * obj->texture_width);
		map[1] = (int)floor(uv.v * obj->texture_height);
	}
	else
	{
		map[0] = (int)floor(uv.u * 10);
		map[1] = (int)floor(uv.v * 10);
	}
}
