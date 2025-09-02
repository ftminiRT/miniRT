
// #include "minirt.h"

// t_color get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
// {
//     t_vec3  n;
//     double  x;
//     double  y;
//     int     u;
//     int     v;

//     n = rt->get_norm[obj->type](obj, hit_point);
//     if (obj->type == OT_SPHERE)
//     {
//         x = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
//         y = 0.5 - asin(n.y) / M_PI;
//         u = floor(x * 10);
//         v = floor(y * 10);
//         if ((u + v) % 2 == 0)
//             return (t_color){0,0,0};
//         return (t_color){255,255,255};
//     }
//     return (t_color){255,0,255};
// }

#include "minirt.h"

static void get_plane_uv(t_obj *obj, t_vec3 hit_point, double *u, double *v)
{
    // Choisir un vecteur arbitraire non colinéaire à la normale
    t_vec3 ref = fabs(obj->n.y) < 0.9 ? (t_vec3){0, 1, 0} : (t_vec3){1, 0, 0};

    // Construire deux axes tangents au plan
    t_vec3 tangent = vec3_normalized(vec3_cross(ref, obj->n));
    t_vec3 bitangent = vec3_cross(obj->n, tangent);

    // Projeter le point sur cette base locale
    t_vec3 rel = vec3_sub(hit_point, obj->pt); // position relative par rapport au centre du plan
    *u = vec3_dot(rel, tangent) / 100;
    *v = vec3_dot(rel, bitangent) / 100;
}

int ft_clamp(double x, int min, int max)
{
    x > max ? x = max : 0;
    x < min ? x = min : 0;
    return(x);
}

t_color get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
    double u = 0, v = 0;
    int iu = 0;
    int iv = 0;
    int checker;

    (void)rt;

    if (obj->type == OT_PLANE)
    {
        get_plane_uv(obj, hit_point, &u, &v);
        iu = (int)floor(u * 10);
        iv = (int)floor(v * 10);
    }
    else if (obj->type == OT_CYL)
    {
        // Corps du cylindre
        if (hit_point.y > obj->pt.y && hit_point.y < obj->pt.y + obj->scal2)
        {
            double theta = atan2(hit_point.z - obj->pt.z,
                                 hit_point.x - obj->pt.x); // [-π, π]
            u = (theta + M_PI) / (2.0 * M_PI);           // [0,1]
            v = (hit_point.y - obj->pt.y) / obj->scal2; // [0,1]
        }
        else // Disques supérieur et inférieur
        {
            u = (hit_point.x - obj->pt.x + obj->scal) / (2.0 * obj->scal); // de 0 à 1
            v = (hit_point.z - obj->pt.z + obj->scal) / (2.0 * obj->scal); // de 0 à 1
            iu = (int)(u * 10);
            iv = (int)(v * 10);
        }
    }
    else if (obj->type == OT_SPHERE)
    {
        t_vec3 d = vec3_normalized(vec3_sub(hit_point, obj->pt));
        u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
        v = 0.5 - asin(d.y) / M_PI;
        iu = (int)floor(u * 10);
        iv = (int)floor(v * 10);
    }
    
    else
        return (obj->color); // magenta si type inconnu
    checker = (iu + iv) % 2;

    return (checker == 0) ? obj->color : (t_color){0,0,0};
}
