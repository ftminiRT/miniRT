#include "minirt.h"

int	ft_clamp(double x, int min, int max)
{
	if (x > max)
		x = max;
	if (x < min)
		x = min;
	return (x);
}

void	get_plane_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	ref;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	rel;
	double	u;
	double	v;

	ref = fabs(obj->n.y) < 0.9 ? (t_vec3){0, 1, 0} : (t_vec3){1, 0, 0};
	tangent = vec3_normalized(vec3_cross(ref, obj->n));
	bitangent = vec3_cross(obj->n, tangent);
	rel = vec3_sub(hit_point, obj->pt);
	u = vec3_dot(rel, tangent) / 100.0;
	v = vec3_dot(rel, bitangent) / 100.0;
	map[0] = (int)floor(u);
	map[1] = (int)floor(v);
}

void	get_sphere_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	d;
	double	u;
	double	v;

	(void)obj;
	d = vec3_normalized(vec3_sub(hit_point, obj->pt));
	u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
	v = 0.5 - asin(d.y) / M_PI;
	map[0] = (int)floor(u * 10);
	map[1] = (int)floor(v * 10);
}

void	get_torus_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	rel;
	double	u, v, theta;
	double	R;

	R = obj->scal2; // grand rayon
	rel = vec3_sub(hit_point, obj->pt);

	// projeter sur le plan perpendiculaire à l'axe
	theta = atan2(rel.z, rel.x);
	if (theta < 0)
		theta += 2.0 * M_PI;
	u = theta / (2.0 * M_PI);

	// coordonnée le long de l'axe du trou
	v = (vec3_dot(rel, obj->n) + R) / (2.0 * R);

	map[0] = (int)floor(u * 10.0);
	map[1] = (int)floor(v * 10.0);
}

void	get_moebius_uv(t_obj *obj, t_vec3 p, int map[2])
{
	t_vec3	rel;
	double	u, v;
	double	R, w; // R = rayon du cercle central, w = demi-largeur de la bande

	R = obj->scal2;     // grand rayon
	w = obj->scal;      // demi-largeur de la bande
	rel = vec3_sub(p, obj->pt);

	// Calculer u : angle autour du cercle central
	u = atan2(rel.y, rel.x);
	if (u < 0)
		u += 2.0 * M_PI;

	// Calculer v : position sur la largeur de la bande
	// projeter sur le vecteur perpendiculaire au cercle central
	v = rel.z / w;
	if (v > 1.0) v = 1.0;
	if (v < -1.0) v = -1.0;

	map[0] = (int)floor(u / (2.0 * M_PI) * 10.0);
	map[1] = (int)floor((v + 1.0) * 5.0); // v ∈ [-1,1] → 0..10
}

t_color	get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
	int	map[2];
	int	checker;

	(void)rt;
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

	checker = (map[0] + map[1]) % 2;
	if (checker == 0)
		return (obj->color);
	return ((t_color){0, 0, 0});
}


// t_color	get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
// {
// 	int	map[2];
// 	int	checker;

// 	(void)rt;
// 	if (obj->type == OT_PLANE)
// 		get_plane_uv(obj, hit_point, map);
// 	else if (obj->type == OT_SPHERE)
// 		get_sphere_uv(obj, hit_point, map);
// 	else if (obj->type == OT_CYL)
// 		get_cylinder_uv(obj, hit_point, map);
// 	else
// 		return (obj->color);
// 	checker = (map[0] + map[1]) % 2;
// 	if (checker == 0)
// 		return (obj->color);
// 	return ((t_color){0, 0, 0});
// }
