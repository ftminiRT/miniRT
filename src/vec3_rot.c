#include "minirt.h"
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