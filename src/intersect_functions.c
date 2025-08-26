#include "minirt.h"

double    hit_sphere(t_ray *ray, t_obj *s)
{
    double  b;
    double  c;
    double  delta;
    double  sqrt_d;
    double  hit1;
    double  hit2;
    t_vec3  oc;

    oc = vec3_sub(ray->pt, s->pt);
    b = vec3_dot(oc, ray->dir);
    c = vec3_dot(oc, oc) - s->scal * s->scal;
    delta = b * b - c;
    if (delta < 0)
        return (INFINITY);
    sqrt_d = sqrt(delta);
    hit1 = -b - sqrt_d;
    hit2 = -b + sqrt_d;
    if (hit1 > EPSILON)
        return (hit1);
    if (hit2 > EPSILON)
        return (hit2);
    return (INFINITY);
}

double    hit_plane(t_ray *r, t_obj *p)
{
    double  a;
    double  b;
    double  t;


    a = vec3_dot(r->dir, p->n);
    b = vec3_dot(p->n, vec3_sub(r->pt, p->pt));
    if (fabs(a) < EPSILON)
        return (INFINITY);
    t = -b / a;
    if (t < EPSILON)
        return (INFINITY);
    return (t);
}

double hit_cylinder(t_ray *ray, t_obj *cy)
{
    t_vec3 oc = vec3_sub(ray->pt, cy->pt);

    double d_dot_n = vec3_dot(ray->dir, cy->n);
    double oc_dot_n = vec3_dot(oc, cy->n);

    t_vec3 d_proj = vec3_sub(ray->dir, vec3_scalmult(d_dot_n, cy->n));
    t_vec3 oc_proj = vec3_sub(oc, vec3_scalmult(oc_dot_n, cy->n));

    double a = vec3_dot(d_proj, d_proj);
    double b = 2 * vec3_dot(d_proj, oc_proj);
    double c = vec3_dot(oc_proj, oc_proj) - cy->scal * cy->scal;

    double delta = b * b - 4 * a * c;
    if (delta < 0)
        return INFINITY;

    double sqrt_d = sqrt(delta);
    double t1 = (-b - sqrt_d) / (2 * a);
    double t2 = (-b + sqrt_d) / (2 * a);

    for (int i = 0; i < 2; i++)
    {
        double t = (i == 0) ? t1 : t2;
        if (t < EPSILON)
            continue;
        t_vec3 p = vec3_add(ray->pt, vec3_scalmult(t, ray->dir));
        t_vec3 from_center = vec3_sub(p, cy->pt);
        double h = vec3_dot(from_center, cy->n);
        if (fabs(h) <= cy->scal2 / 2.0)
            return t;
    }

    return INFINITY;
}
