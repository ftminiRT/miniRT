#include "minirt.h"

static t_vec3	torus_local_hit(t_obj *obj, t_vec3 hit_point, t_torusnorm *comp)
{
	t_vec3	rel;

	rel = vec3_sub(hit_point, obj->pt);
	comp->local_hit = (t_vec3){vec3_dot(rel, comp->b.u), vec3_dot(rel,
			comp->b.w), vec3_dot(rel, comp->b.v)};
	comp->center_to_hit = (t_vec3){comp->local_hit.x, 0, comp->local_hit.z};
	vec3_normalize(&comp->center_to_hit);
	comp->center_ring = vec3_scalmult(comp->br, comp->center_to_hit);
	return (vec3_sub(comp->local_hit, comp->center_ring));
}

static t_vec3	torus_geo_normal(t_torusnorm *comp, t_vec3 geo_normal)
{
	vec3_normalize(&geo_normal);
	return (vec3_add(vec3_add(vec3_scalmult(geo_normal.x, comp->b.u),
				vec3_scalmult(geo_normal.y, comp->b.w)),
			vec3_scalmult(geo_normal.z, comp->b.v)));
}

static t_vec3	torus_apply_normal_mapping(t_env *rt, t_obj *obj,
		t_vec3 geo_normal, t_torusnorm comp)
{
	t_normap	normap;

	if (!obj->normal_map_data || rt->basicrt)
		return (geo_normal);
	normap.tangent = vec3_cross(obj->n, geo_normal);
	vec3_normalize(&normap.tangent);
	normap.bitangent = obj->n;
	normap.u = atan2(comp.center_to_hit.z, comp.center_to_hit.x) / (2.0 * M_PI)
		+ 0.5;
	normap.v = 0.5 + comp.local_hit.y / (2.0 * comp.r);
	return (apply_normal_mapping(geo_normal, normap.tangent, normap.bitangent,
			sample_normal_map(obj, normap.u, normap.v)));
}

t_vec3	torus_normal(t_obj *obj, t_vec3 hit_point, t_env *rt)
{
	t_torusnorm	comp;
	t_vec3		geo_normal;

	comp.br = obj->scal2;
	comp.r = obj->scal;
	init_base(obj, &comp.b);
	geo_normal = torus_local_hit(obj, hit_point, &comp);
	geo_normal = torus_geo_normal(&comp, geo_normal);
	return (torus_apply_normal_mapping(rt, obj, geo_normal, comp));
}
