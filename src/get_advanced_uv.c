#include "minirt.h"


void get_torus_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
    t_vec3 rel;
    double u, v, theta;
    double R;
    
    R = obj->scal2; // grand rayon
    rel = vec3_sub(hit_point, obj->pt);
    
    // projeter sur le plan perpendiculaire à l'axe
    theta = atan2(rel.z, rel.x);
    if (theta < 0)
        theta += 2.0 * M_PI;
    u = theta / (2.0 * M_PI);
    
    // coordonnée le long de l'axe du trou
    v = (vec3_dot(rel, obj->n) + R) / (2.0 * R);
    
    // CHANGÉ: au lieu de (int)floor(u * 10.0) et (int)floor(v * 10.0)

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
    double u, v;
    double R, w; // R = rayon du cercle central, w = demi-largeur de la bande
    
    R = obj->scal2; // grand rayon
    w = obj->scal; // demi-largeur de la bande
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
    
    // CHANGÉ: au lieu de (int)floor(u / (2.0 * M_PI) * 10.0) et (int)floor((v + 1.0) * 5.0)

    if (!obj->checkered)
    {
        map[0] = (int)floor(u / (2.0 * M_PI) * obj->texture_width);
        map[1] = (int)floor((v + 1.0) * 0.5 * obj->texture_height);
    }
    else
    {
        map[0] = (int)floor(u / (2.0 * M_PI) * 10);
        map[1] = (int)floor((v + 1.0) * 0.5 * 5);
    }
}