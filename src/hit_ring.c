#include "minirt.h"

static void	change_basis(t_ray *ray, t_obj *obj, t_vec3 *ro, t_vec3 *rd)
{
	t_basis	b;
	t_vec3	tmp;

	init_base(obj, &b);
	tmp = vec3_sub(ray->pt, obj->pt);
	*ro = (t_vec3){vec3_dot(tmp, b.u), vec3_dot(tmp, b.w), vec3_dot(tmp, b.v)};
	*rd = (t_vec3){vec3_dot(ray->dir, b.u), vec3_dot(ray->dir, b.w),
		vec3_dot(ray->dir, b.v)};
}

static void	apply_scaling(t_vec3 *ro, t_vec3 *rd, t_obj *obj, double *R)
{
	*ro = (t_vec3){ro->x / obj->scal, ro->y / obj->scal3, ro->z / obj->scal};
	*rd = (t_vec3){rd->x / obj->scal, rd->y / obj->scal3, rd->z / obj->scal};
	*R /= obj->scal;
}

static void	compute_coeffs_one_ring(t_ray *ray, t_obj *obj, double *a)
{
	t_ring	r;

	r.r = obj->scal2;
	change_basis(ray, obj, &r.ro, &r.rd);
	apply_scaling(&r.ro, &r.rd, obj, &r.r);
	r.dd = vec3_dot(r.rd, r.rd);
	r.e = vec3_dot(r.ro, r.ro) - (r.r * r.r + 1.0);
	r.f = vec3_dot(r.ro, r.rd);
	r.four_br2 = 4.0 * r.r * r.r;
	a[0] = (r.e * r.e - r.four_br2 * (1.0 - r.ro.y * r.ro.y)) / (r.dd * r.dd);
	a[1] = (4.0 * r.f * r.e + 2.0 * r.four_br2 * r.ro.y * r.rd.y) / (r.dd
			* r.dd);
	a[2] = (2.0 * r.dd * r.e + 4.0 * r.f * r.f + r.four_br2 * r.rd.y * r.rd.y)
		/ (r.dd * r.dd);
	a[3] = (4.0 * r.dd * r.f) / (r.dd * r.dd);
}

double	hit_ring(t_ray *ray, t_obj *obj)
{
	double	coeffs[4];
	double	roots[4];
	int		n;
	int		i;

	if (!obj->scal || !obj->scal2 || !obj->scal3)
		return (INFINITY);
	compute_coeffs_one_ring(ray, obj, coeffs);
	n = solve_quartic(coeffs, roots);
	if (n == 0)
		return (INFINITY);
	i = 0;
	while (i < n)
	{
		if (roots[i] > 0)
			return (roots[i]);
		i++;
	}
	return (INFINITY);
}
