#include "minirt.h"

static t_vec3	cone_geo_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3 radial;
	double h;
    
    h = vec3_dot(vec3_sub(hit_point, vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))), obj->n);
	if (h >= obj->scal2 - EPSILON)
		return obj->n;

	radial = vec3_sub(vec3_sub(hit_point, vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))),
					  vec3_scalmult(vec3_dot(vec3_sub(hit_point, vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))),
											 obj->n), obj->n));
	t_vec3 geo_normal = vec3_sub(vec3_scalmult(h, radial),
								 vec3_scalmult(vec3_dot(radial, radial)/h, obj->n));
	vec3_normalize(&geo_normal);
	return geo_normal;
}


t_vec3	cone_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3 geo_normal = cone_geo_normal(obj, hit_point);
	t_vec3 map_normal;
	t_normap normap;

	if (!obj->normal_map_data)
		return geo_normal;
	if (fabs(geo_normal.x) < 0.9)
		normap.tangent = vec3_cross(geo_normal, (t_vec3){1,0,0});
	else
		normap.tangent = vec3_cross(geo_normal, (t_vec3){0,1,0});
	vec3_normalize(&normap.tangent);
	normap.bitangent = vec3_cross(geo_normal, normap.tangent);
	vec3_normalize(&normap.bitangent);
	normap.h = vec3_dot(vec3_sub(hit_point, vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))), obj->n);
	if (normap.h >= obj->scal2 - EPSILON)
	{
		t_vec3 local = vec3_sub(hit_point, obj->pt);
		normap.u = (vec3_dot(local, normap.tangent)/obj->scal + 1.0)*0.5;
		normap.v = (vec3_dot(local, normap.bitangent)/obj->scal + 1.0)*0.5;
	}
	else
	{
		t_vec3 radial = vec3_sub(vec3_sub(hit_point, vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))),
								 vec3_scalmult(vec3_dot(vec3_sub(hit_point, vec3_sub(obj->pt, vec3_scalmult(obj->scal2, obj->n))),
													 obj->n), obj->n));
		normap.u = atan2(vec3_dot(radial, normap.bitangent), vec3_dot(radial, normap.tangent))/(2.0*M_PI)+0.5;
		normap.v = normap.h/obj->scal2;
	}
	map_normal = sample_normal_map(obj, normap.u, normap.v);
	return apply_normal_mapping(geo_normal, normap.tangent, normap.bitangent, map_normal);
}
