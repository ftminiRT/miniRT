#include "minirt.h"

void		handle_r_and_zarr(double *r, double *zarr)
{
	r[0] = zarr[0];
	r[1] = zarr[1];
	r[2] = zarr[2];
	r[3] = zarr[3];
}
static void	compute_coeffs(t_ray *ray, t_obj *obj, double *a)
{
	t_vec3	u, v, w;
	t_vec3	ro, rd;
	double	R, r;
	double	dd, e, f, four_R2;

	// R = grand rayon (scal2), r = petit rayon (scal)
	R = obj->scal2;
	r = obj->scal;

	// Construire base locale (u,v,w) avec w = axe du tore
	w = vec3_normalized(obj->n);
	if (fabs(w.y) < 0.9)
		u = vec3_normalized(vec3_cross((t_vec3){0, 1, 0}, w));
	else
		u = vec3_normalized(vec3_cross((t_vec3){1, 0, 0}, w));
	v = vec3_cross(w, u);

	// Changer de base : world -> local
	ro = (t_vec3){
		vec3_dot(vec3_sub(ray->pt, obj->pt), u),
		vec3_dot(vec3_sub(ray->pt, obj->pt), w), // axe du trou = Y
		vec3_dot(vec3_sub(ray->pt, obj->pt), v)
	};
	rd = (t_vec3){
		vec3_dot(ray->dir, u),
		vec3_dot(ray->dir, w),
		vec3_dot(ray->dir, v)
	};

	dd = vec3_dot(rd, rd);
	e = vec3_dot(ro, ro) - (R * R + r * r);
	f = vec3_dot(ro, rd);
	four_R2 = 4.0 * R * R;

	// Coefficients quartiques
	a[0] = (e * e - four_R2 * (r * r - ro.y * ro.y)) / (dd * dd);
	a[1] = (4.0 * f * e + 2.0 * four_R2 * ro.y * rd.y) / (dd * dd);
	a[2] = (2.0 * dd * e + 4.0 * f * f + four_R2 * rd.y * rd.y) / (dd * dd);
	a[3] = (4.0 * dd * f) / (dd * dd);
}

double		hit_torus(t_ray *ray, t_obj *obj)
{
	double	a[4];
	double	roots[4];
	int		num_real_roots;

	compute_coeffs(ray, obj, a);
	num_real_roots = solve_quartic(a, roots);
	if (num_real_roots == 0)
		return (INFINITY);
	if (num_real_roots == 2)
	{
		if (roots[0] < 0)
        {
            if (roots[1] < 0)
                return (INFINITY);
            else
                return (roots[1]);
        }
        else
			return (roots[0]);
	}
	num_real_roots = 0;
	while (num_real_roots < 4)
	{
		if (roots[num_real_roots] > 0)
			return (roots[num_real_roots]);
		num_real_roots++;
	}
	return (INFINITY);
}

// t_vec3		torus_normal(t_obj *obj, t_vec3 hit_point)
// {
// 	t_vec3	ret;

// 	ret.x = 4 * hit_point.x * (vec3_dot(hit_point, hit_point) -
//         (obj->scal2 + obj->scal));
// 	ret.y = 4 * hit_point.y * (vec3_dot(hit_point, hit_point) -
//         (obj->scal2 + obj->scal) + 2 * obj->scal2);
// 	ret.z = 4 * hit_point.z * (vec3_dot(hit_point, hit_point) -
//         (obj->scal2 + obj->scal));
// 	return (vec3_normalized(ret));
// }
t_vec3 torus_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3 geo_normal;
	t_vec3 tangent;
	t_vec3 bitangent;
	t_vec3 map_normal;
	t_normap normap;

	// Normale géométrique
	geo_normal = vec3_sub(hit_point, obj->pt);
	geo_normal.y = 0; // projeter sur plan XY pour l'axe du trou
	vec3_normalize(&geo_normal);

	// Si pas de normal map, retourner normale géométrique
	if (!obj->normal_map_data)
		return (geo_normal);

	// Base tangentielle
	tangent = vec3_cross(obj->n, geo_normal);
	vec3_normalize(&tangent);
	bitangent = obj->n;

	// Coordonnées UV pour le bump
	normap.u = atan2(geo_normal.z, geo_normal.x) / (2.0 * M_PI) + 0.5;
	normap.v = 0.5 + vec3_dot(hit_point, obj->n) / obj->scal2;

	// Sample bump map
	map_normal = sample_normal_map(obj, normap.u, normap.v);

	// Appliquer la perturbation
	return apply_normal_mapping(geo_normal, tangent, bitangent, map_normal);
}
