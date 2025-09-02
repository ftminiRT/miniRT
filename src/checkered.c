
#include "minirt.h"

t_color get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
    t_vec3  n;
    double  x;
    double  y;
    int     u;
    int     v;

    n = rt->get_norm[obj->type](obj, hit_point);
    if (obj->type == OT_SPHERE)
    {
        x = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
        y = 0.5 - asin(n.y) / M_PI;
        u = floor(x * 10);
        v = floor(y * 10);
        if ((u + v) % 2 == 0)
            return (t_color){0,0,0};
        return (t_color){255,255,255};
    }
    return (t_color){255,0,255};
}