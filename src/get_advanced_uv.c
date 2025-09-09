#include "minirt.h"

void	get_torus_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
	t_vec3	rel;
	double	u;
	double	v;
	double	theta;

	rel = vec3_sub(hit_point, obj->pt);
	theta = atan2(rel.z, rel.x);
	if (theta < 0)
		theta += 2.0 * M_PI;
	u = theta / (2.0 * M_PI);
	v = (vec3_dot(rel, obj->n) + obj->scal2) / (2.0 * obj->scal2);
	if (!obj->checkered)
	{
		map[0] = (int)floor(u * obj->texture_width);
		map[1] = (int)floor(v * obj->texture_height);
	}
	else
	{
		map[0] = (int)floor(u * 10);
		map[1] = (int)floor(v * 10);
	}
}

void get_moebius_uv(t_obj *obj, t_vec3 p, int map[2])
{
    t_vec3 rel;
    t_basis b;
    t_vec3 local_hit;
    double t, s;
    double eps = 1e-6;
    
    // Transformer en coordonnées locales (comme dans la normale)
    b = make_basis(obj->n);
    rel = vec3_sub(p, obj->pt);
    local_hit = world_to_local_vec(rel, b);
    
    // Récupérer les vrais paramètres du Möbius
    t = atan2(local_hit.y, local_hit.x);
    if (t < 0) t += 2.0 * M_PI;
    
    if (fabs(sin(t / 2)) > eps)
        s = local_hit.z / sin(t / 2);
    else
        s = (local_hit.x / cos(t) - obj->scal) / cos(t / 2);
    
    // UV basé sur les vrais paramètres
    double u = t / (2.0 * M_PI);
    double v = (s / obj->max + 1.0) * 0.5; // normaliser s entre 0 et 1
    
    // Clamper pour éviter les débordements
    u = fmax(0.0, fmin(0.999999, u));
    v = fmax(0.0, fmin(0.999999, v));
    
    if (!obj->checkered) {
        map[0] = (int)floor(u * obj->texture_width);
        map[1] = (int)floor(v * obj->texture_height);
    } else {
        map[0] = (int)floor(u * 10);
        map[1] = (int)floor(v * 5);
    }
}