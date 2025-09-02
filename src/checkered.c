
// #include "minirt.h"


#include "minirt.h"

int ft_clamp(double x, int min, int max)
{
    x > max ? x = max : 0;
    x < min ? x = min : 0;
    return(x);
}

// t_color get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
// {
//     double u = 0, v = 0;
//     int iu = 0;
//     int iv = 0;
//     int checker;

//     (void)rt;

//     if (obj->type == OT_PLANE)
//     {
//         get_plane_uv(obj, hit_point, &u, &v);
//         iu = (int)floor(u * 10);
//         iv = (int)floor(v * 10);
//     }
//     else if (obj->type == OT_SPHERE)
//     {
//         t_vec3 d = vec3_normalized(vec3_sub(hit_point, obj->pt));
//         u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
//         v = 0.5 - asin(d.y) / M_PI;
//         iu = (int)floor(u * 10);
//         iv = (int)floor(v * 10);
//     }
    
//     else
//         return (obj->color); // magenta si type inconnu
//     checker = (iu + iv) % 2;

//     return (checker == 0) ? obj->color : (t_color){0,0,0};
// }

t_color get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
    double u = 0, v = 0;
    int iu = 0, iv = 0;
    int checker;

    (void)rt;

    if (obj->type == OT_PLANE)
    {
        // Repère local du plan
        t_vec3 ref = fabs(obj->n.y) < 0.9 ? (t_vec3){0, 1, 0} : (t_vec3){1, 0, 0};
        t_vec3 tangent = vec3_normalized(vec3_cross(ref, obj->n));
        t_vec3 bitangent = vec3_cross(obj->n, tangent);

        t_vec3 rel = vec3_sub(hit_point, obj->pt);
        u = vec3_dot(rel, tangent) / 100.0;
        v = vec3_dot(rel, bitangent) / 100.0;
        iu = (int)floor(u);
        iv = (int)floor(v);
    }
    else if (obj->type == OT_SPHERE)
    {
        t_vec3 d = vec3_normalized(vec3_sub(hit_point, obj->pt));
        u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
        v = 0.5 - asin(d.y) / M_PI;
        iu = (int)floor(u * 10);
        iv = (int)floor(v * 10);
    }
else if (obj->type == OT_CYL)
{
    // Calcul de la hauteur relative au centre du cylindre
    t_vec3 from_center = vec3_sub(hit_point, obj->pt);
    double h = vec3_dot(from_center, obj->n);
    
    // Corps du cylindre (dans les limites de hauteur)
    if (fabs(h) <= obj->scal2 / 2.0 - EPSILON)
    {
        // Projette le point sur le plan perpendiculaire à l'axe
        t_vec3 radial = vec3_sub(from_center, vec3_scalmult(h, obj->n));
        
        // Calcul de theta dans le repère local du cylindre
        // On crée un repère orthonormé à partir de l'axe du cylindre
        t_vec3 u_vec, v_vec;
        if (fabs(obj->n.x) < 0.9)
            u_vec = vec3_cross(obj->n, (t_vec3){1, 0, 0});
        else
            u_vec = vec3_cross(obj->n, (t_vec3){0, 1, 0});
        vec3_normalize(&u_vec);  // Modifie en place
        v_vec = vec3_cross(obj->n, u_vec);
        
        double theta = atan2(vec3_dot(radial, v_vec), vec3_dot(radial, u_vec));
        if (theta < 0)
            theta += 2.0 * M_PI;
            
        u = theta / (2.0 * M_PI);
        v = (h + obj->scal2 / 2.0) / obj->scal2;
        
        iu = (int)floor(u * 10.0);
        iv = (int)floor(v * 10.0);
        
        iu = iu % 10;
        if (iu < 0) iu += 10;
    }
    // Caps du cylindre
    else
    {
        // Détermine quel cap on touche
        t_vec3 center;
        if (h < 0)
            center = vec3_add(obj->pt, vec3_scalmult(-obj->scal2 / 2.0, obj->n));
        else
            center = vec3_add(obj->pt, vec3_scalmult(obj->scal2 / 2.0, obj->n));
            
        t_vec3 local = vec3_sub(hit_point, center);
        
        // Utilise le même repère que pour le corps du cylindre
        t_vec3 u_vec, v_vec;
        if (fabs(obj->n.x) < 0.9)
            u_vec = vec3_cross(obj->n, (t_vec3){1, 0, 0});
        else
            u_vec = vec3_cross(obj->n, (t_vec3){0, 1, 0});
        vec3_normalize(&u_vec);  // Modifie en place
        v_vec = vec3_cross(obj->n, u_vec);
        
        // Mapping cartésien simple pour debug
        double lx = vec3_dot(local, u_vec) / obj->scal;
        double lz = vec3_dot(local, v_vec) / obj->scal;
        
        iu = (int)floor((lx + 1.0) * 5.0);  // De -1 à 1 -> 0 à 10
        iv = (int)floor((lz + 1.0) * 5.0);
        
        iu = ((iu % 10) + 10) % 10;
        iv = ((iv % 10) + 10) % 10;
    }
}


    else
        return (obj->color);

    checker = (iu + iv) % 2;
    return (checker == 0) ? obj->color : (t_color){0, 0, 0};
}
