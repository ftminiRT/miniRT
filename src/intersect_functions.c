#include "minirt.h"

bool    hit_sphere(t_ray *ray, t_sphere s)
{
    double  a;
    double  b;
    double  c;
    double  delta;
    double  hit;

    a = vec3_dot(ray->dir, ray->dir);
    printf("ray->dir: {%f, %f, %f}\n", ray->dir.x, ray->dir.y, ray->dir.z);
    b = 2 * (ray->dir.x * (ray->pt.x - s.center.x) +
    ray->dir.y * (ray->pt.y - s.center.y) +
    ray->dir.z * (ray->pt.z - s.center.z));
    c = (ray->pt.x - s.center.x) * (ray->pt.x - s.center.x) +
    (ray->pt.y - s.center.y) * (ray->pt.y - s.center.y) +
    (ray->pt.z - s.center.z) * (ray->pt.z - s.center.z) - s.r * s.r;
    delta = b * b - 4 * a * c;
    if (delta < 0)
        return (false);
    else
    {
        hit = (-b - sqrt(delta)) / (2 * a);
        if (hit < 0)
        {
            hit = (-b + sqrt(delta)) / (2 * a);
            if (hit < 0)
                return (false);
        }
        if (ray->hit > 0 && hit > ray->hit)
            return (false);
        printf("sphere hit %f a:%f b:%f c:%f\n", hit, a, b, c);
        ray->hit = hit;
        return (true);
    }
}

bool    hit_plane(t_ray *r, t_plane p)
{
    double  a;
    double  b;

    a = vec3_dot(r->dir, p.n);
    b = vec3_dot(p.n, vec3_sub(r->pt, p.pt));
    if (a == 0)
        return (false);
    if (r->hit > 0 && (-b / a) > r->hit)
        return (false);
    else if (-b / a < 0)
    {
        r->hit = -b / a;
        return (true);
    }
    else
        return (false);
}

bool    hit_cylinder(t_ray *ray, t_cyl cy)
{
    double  a;
    double  b;
    double  c;
    double  delta;
    double  hit;
    t_vec3  new_o;
    double  smn0; // a rename
    double  smn1; // a rename
    double  r;

    if (cy.n.x == 0 && cy.n.y == 0 && cy.n.z == 0)
        return (false);
    new_o = vec3_sub(ray->pt, cy.center);
    smn0 = vec3_dot(ray->dir, cy.n);
    smn1 = vec3_dot(new_o, cy.n);
    r = cy.r;
    a = vec3_dot(ray->dir, ray->dir) - smn0 * smn0;
    b = 2 * (vec3_dot(ray->dir, new_o) - smn0 * smn1);
    c = vec3_dot(new_o, new_o) - smn1 * smn1 - r * r;
    delta = b * b - 4 * a * c;
    if (delta < 0)
        return (false);
    else
    {
        hit = (-b - sqrt(delta)) / 2 * a;
        if (hit < 0)
        {
            hit = (-b + sqrt(delta)) / (2 * a);
            if (hit < 0)
                return (false);
        }
        if (ray->hit > 0 && hit > ray->hit)
            return (hit);
        ray->hit = hit;
        return (true);
    }
}
