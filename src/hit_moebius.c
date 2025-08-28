/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_moebius.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:44:09 by tbeauman          #+#    #+#             */
/*   Updated: 2025/08/28 19:47:16 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ---------------- Basis & transforms ---------------- */

typedef struct s_basis
{
    t_vec3 u;
    t_vec3 v;
    t_vec3 w;
}   t_basis;

static t_basis make_basis(t_vec3 n)
{
    t_basis b;
    t_vec3 tmp;

    b.w = vec3_normalized(n);
    if (fabs(b.w.x) < 1e-6 && fabs(b.w.z) < 1e-6)
        tmp = (t_vec3){1, 0, 0}; // éviter colinéarité si n ~ (0,±1,0)
    else
        tmp = (t_vec3){0, 1, 0};
    b.u = vec3_normalized(vec3_cross(tmp, b.w));
    b.v = vec3_cross(b.w, b.u);
    return b;
}

static t_vec3 world_to_local_vec(t_vec3 v, t_basis b)
{
    return (t_vec3){
        vec3_dot(v, b.u),
        vec3_dot(v, b.v),
        vec3_dot(v, b.w)
    };
}

static t_vec3 local_to_world_vec(t_vec3 v, t_basis b)
{
    return (t_vec3){
        b.u.x * v.x + b.v.x * v.y + b.w.x * v.z,
        b.u.y * v.x + b.v.y * v.y + b.w.y * v.z,
        b.u.z * v.x + b.v.z * v.y + b.w.z * v.z
    };
}

static t_ray world_to_local_ray(t_ray r, t_obj *obj, t_basis b)
{
    t_ray out;

    out.pt = world_to_local_vec(vec3_sub(r.pt, obj->pt), b);
    out.dir = world_to_local_vec(r.dir, b);
    return out;
}

/* ---------------- Ton code existant ---------------- */

int dblsgn(double x)
{
    if (x < -EPSILON)
        return (-1);
    return (x > EPSILON);
}

int inside(t_obj *m, t_vec3 h)
{
    double t;
    double s;

    t = atan2(h.y, h.x);
    if (dblsgn(sin(t / 2)) != 0)
        s = h.z / sin(t / 2);
    else
        s = dblsgn(cos(t)) ? (h.x / cos(t) - m->scal) / cos(t / 2) :
            (h.y / sin(t) - m->scal) / cos(t / 2);
    h.x -= (m->scal + s * cos(t / 2)) * cos(t);
    h.y -= (m->scal + s * cos(t / 2)) * sin(t);
    h.z -= s * sin(t / 2);
    if (dblsgn(h.x * h.x + h.y * h.y + h.z * h.z))
        return (0);
    return (s >= -m->max && s <= m->max);
}

static double choose_mobi_root(double *roots, int ret, t_ray *ray, t_obj *obj)
{
    int     i;
    t_vec3  hit;

    i = 0;
    while (i < ret)
    {
        if (roots[i] > EPSILON)
        {
            hit = vec3_add(vec3_scalmult(roots[i], ray->dir), ray->pt);
            if (inside(obj, hit))
                return (roots[i]);
        }
        i++;
    }
    return (INFINITY);
}

static void init_coeffs(t_moebius m, double *coeff)
{
    coeff[3] = m.c * m.c * m.e + m.e * m.e * m.e - 2 * m.c * m.c * m.g
        - 2 * m.e * m.e * m.g + m.e * m.g * m.g;
    coeff[0] = (m.b * m.b * m.d + m.d * m.d * m.d - 2 * m.b * m.b * m.f
        - 2 * m.d * m.d * m.f + m.d * m.f * m.f - 2 * m.b * m.f * m.a
        - m.d * m.a * m.a) / coeff[3];
    coeff[1] = (m.e * m.b * m.b - 2 * m.g * m.b * m.b + 2 * m.c * m.b * m.d
        + 3 * m.e * m.d * m.d - 2 * m.g * m.d * m.d - 4 * m.c * m.b * m.f
        - 4 * m.e * m.d * m.f + 2 * m.g * m.d * m.f + m.e * m.f * m.f
        - 2 * m.g * m.b * m.a - 2 * m.c * m.f * m.a - m.e * m.a * m.a)
        / coeff[3];
    coeff[2] = (2 * m.c * m.e * m.b - 4 * m.c * m.g * m.b + m.c * m.c * m.d
        + 3 * m.e * m.e * m.d - 4 * m.e * m.g * m.d + m.g * m.g * m.d
        - 2 * m.c * m.c * m.f - 2 * m.e * m.e * m.f + 2 * m.e * m.g * m.f
        - 2 * m.c * m.g * m.a) / coeff[3];
}

/* -------- Intersection avec translation/rotation -------- */

double hit_moebius(t_ray *ray, t_obj *obj)
{
    double      a[4];
    double      root[3];
    t_moebius   m;
    int         ret;
    t_basis     b;
    t_ray       local_ray;

    b = make_basis(obj->n);
    local_ray = world_to_local_ray(*ray, obj, b);

    m.a = obj->scal;
    m.b = local_ray.pt.x;
    m.c = local_ray.dir.x;
    m.d = local_ray.pt.y;
    m.e = local_ray.dir.y;
    m.f = local_ray.pt.z;
    m.g = local_ray.dir.z;
    init_coeffs(m, a);
    ret = solve_cubic(a, root);
    return (choose_mobi_root(root, ret, &local_ray, obj));
}

/* -------- Normale avec re-projection en monde -------- */

t_vec3 moebius_normal(t_obj *obj, t_vec3 hit_point)
{
    t_vec3  local_n;
    t_vec3  world_n;
    t_basis b;

    b = make_basis(obj->n);
    // On suppose hit_point est déjà en repère local ici
    local_n.x = -2 * obj->scal * hit_point.z
        + 2 * hit_point.x * hit_point.y
        - 4 * hit_point.x * hit_point.z;
    local_n.y = -obj->scal2 + hit_point.x * hit_point.x
        + 3 * hit_point.y * hit_point.y
        - 4 * hit_point.y * hit_point.z
        + hit_point.z * hit_point.z;
    local_n.z = -2 * obj->scal * hit_point.x
        - 2 * hit_point.x * hit_point.x
        - 2 * hit_point.y * hit_point.y
        + 2 * hit_point.y * hit_point.z;
    vec3_normalize(&local_n);
    world_n = local_to_world_vec(local_n, b);
    vec3_normalize(&world_n);
    return (world_n);
}
