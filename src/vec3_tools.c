#include "minirt.h"

t_vec3  vec3_add(t_vec3 a, t_vec3 b)
{
    t_vec3  c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return (c);
}

t_vec3  vec3_sub(t_vec3 a, t_vec3 b)
{
    t_vec3  c;

    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return (c);
}

t_vec3  vec3_scalmult(double scal, t_vec3 a)
{
    t_vec3  b;
    
    b.x = scal * a.x;
    b.y = scal * a.y;
    b.z = scal * a.z;
    return (b);
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    return (t_vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

double  vec3_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}
