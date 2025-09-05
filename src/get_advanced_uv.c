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
    double w; // R = rayon du cercle central, w = demi-largeur de la bande
    
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

void get_ring_uv(t_obj *obj, t_vec3 hit_point, int map[2])
{
    t_vec3 rel, u_axis, v_axis, w_axis;
    t_vec3 local;
    double R, a_axis, b_axis;
    double u, v, theta, phi;

    R      = obj->scal2;  // grand rayon
    b_axis = obj->scal;   // petit rayon radial (XY)
    a_axis = obj->scal3;  // petit rayon vertical (Y)

    // construire base locale (w = axe de l'anneau)
    w_axis = vec3_normalized(obj->n);
    if (fabs(w_axis.y) < 0.9)
        u_axis = vec3_normalized(vec3_cross((t_vec3){0,1,0}, w_axis));
    else
        u_axis = vec3_normalized(vec3_cross((t_vec3){1,0,0}, w_axis));
    v_axis = vec3_cross(w_axis, u_axis);

    // passer en coords locales
    rel = vec3_sub(hit_point, obj->pt);
    local = (t_vec3){
        vec3_dot(rel, u_axis),
        vec3_dot(rel, w_axis),
        vec3_dot(rel, v_axis)
    };

    // ===== coord u (autour du grand cercle) =====
    theta = atan2(local.z, local.x);
    if (theta < 0)
        theta += 2.0 * M_PI;
    u = theta / (2.0 * M_PI);

    // ===== coord v (autour de la section elliptique) =====
    // centre du tube sur ce theta
    double cx = R * cos(theta);
    double cz = R * sin(theta);

    // déplacement par rapport au centre de la section
    double dx = local.x - cx;
    double dy = local.y;
    double dz = local.z - cz;

    // ramener ellipse à un cercle : xz/b_axis, y/a_axis
    double ex = dx / b_axis;
    double ez = dz / b_axis;
    double ey = dy / a_axis;

    // angle dans la section elliptique
    phi = atan2(ey, sqrt(ex*ex + ez*ez));
    v = (phi / M_PI) + 0.5; // map [-pi/2,pi/2] -> [0,1]

    // ===== convertir en pixel coords =====
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
