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
    *u = fmod(fabs(vec3_dot(rel, tangent)), 1.0);
    *v = fmod(fabs(vec3_dot(rel, bitangent)), 1.0);
}

int ft_clamp(double x, int min, int max)
{
    x > max ? x = max : 0;
    x < min ? x = min : 0;
    return(x);
}

t_color get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
    double u, v;
    int checker;
    const double scale = 1.0;

    (void)rt;
    if (obj->type == OT_PLANE)
    {
        get_plane_uv(obj, hit_point, &u, &v);
    }
    else if (obj->type == OT_CYL)
    {
        double theta = atan2(hit_point.y - obj->pt.y,
                             hit_point.x - obj->pt.x); // [-π, π]
        u = (theta + M_PI) / (2.0 * M_PI);               // [0,1]
        v = (hit_point.z - obj->pt.z) / obj->scal2;     // normalisé
    }
    else if (obj->type == OT_SPHERE)
    {
        t_vec3  d;
        double  u;
        double  v;
        
        d = vec3_normalized(vec3_sub(hit_point, obj->pt));
        u = 0.5 + atan2(d.z, d.x) / (2 * M_PI);
        v = 0.5 - asin(d.y) / M_PI;
        int iu = (int)(u * 10);
        int iv = (int)(v * 10);
        if ((iu + iv) % 2 == 0)
            return ((t_color){1,1,1});
        else
            return ((t_color){0,0,0});
    }
    else
        return (t_color){1, 1, 1}; // blanc par défaut

    checker = ((int)floor(u / scale) + (int)floor(v / scale)) % 2;
    return (checker == 0) ? (t_color){1, 1, 1} : (t_color){0, 0, 0};
}
