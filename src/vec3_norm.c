#include "minirt.h"

double  vec3_norm(t_vec3 a)
{
    return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

double  vec3_sqnorm(t_vec3 a)
{
    return (a.x * a.x + a.y * a.y + a.z * a.z);
}

void  vec3_normalize(t_vec3 *a)
{
    double  norm;

    if (a->x == 0 && a->y == 0 && a->z == 0)
        error_exit("cant normalize null vector");
    norm = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
    a->x = a->x / norm;
    a->y = a->y / norm;
    a->z = a->z / norm;
}
