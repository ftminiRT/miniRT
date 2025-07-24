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
    b.y = scal * b.y;
    b.z = scal * b.z;
    return (b);
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

double  vec3_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3  vec3_up()
{
    return ((t_vec3) {1, 0, 0});
}

t_vec3  vec3_right()
{
    return ((t_vec3) {0, 1, 0});
}

t_vec3  vec3_rot(t_vec3 *v, int axis, double theta)
{
    t_vec3  r;

    theta *= M_PI / 180;
    r = (t_vec3) { v->x, v->y, v->z };
    if (axis == Z_AXIS)
    {
        r.x = v->x * cos(theta) - v->y * sin(theta);
		r.y = v->x * sin(theta) + v->y * cos(theta);
	}
	if (axis == Y_AXIS)
	{
		r.x = v->x * cos(theta) - v->z * sin(theta);
		r.z = v->x * sin(theta) + v->z * cos(theta);
	}
	if (axis == X_AXIS)
	{
		r.y = v->y * cos(theta) - v->z * sin(theta);
		r.z = v->y * sin(theta) + v->z * cos(theta);
	}
	*v = r;
    return (*v);
}

void    vec3_rotate(t_vec3 *v, t_vec3 r)
{
    if (r.x)
        vec3_rot(v, X_AXIS, r.x);
    if (r.y)
        vec3_rot(v, Y_AXIS, r.y);
    if (r.z)
        vec3_rot(v, Z_AXIS, r.z);
}