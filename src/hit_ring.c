#include "minirt.h"

/*
** hit_one_ring : intersection rayon / tore elliptique (anneau plein LOTR)
** obj->scal2 = grand rayon (R)
** obj->scal  = petit rayon horizontal (b)
** obj->scal3 = petit rayon vertical   (a)
*/
static void compute_coeffs_one_ring(t_ray *ray, t_obj *obj, double *a)
{
    t_vec3 u, v, w;
    t_vec3 ro, rd;
    double R, a_axis, b_axis;

    R      = obj->scal2;  // grand rayon
    b_axis = obj->scal;   // épaisseur radiale
    a_axis = obj->scal3;  // épaisseur verticale

    // base locale
    w = vec3_normalized(obj->n);
    if (fabs(w.y) < 0.9)
        u = vec3_normalized(vec3_cross((t_vec3){0, 1, 0}, w));
    else
        u = vec3_normalized(vec3_cross((t_vec3){1, 0, 0}, w));
    v = vec3_cross(w, u);

    // changer de base
    ro = (t_vec3){
        vec3_dot(vec3_sub(ray->pt, obj->pt), u),
        vec3_dot(vec3_sub(ray->pt, obj->pt), w),
        vec3_dot(vec3_sub(ray->pt, obj->pt), v)
    };
    rd = (t_vec3){
        vec3_dot(ray->dir, u),
        vec3_dot(ray->dir, w),
        vec3_dot(ray->dir, v)
    };

    /*
    ** Trick : on scale les coords pour transformer l’ellipse en cercle
    ** => on ramène à un tore "classique" dans l’espace scalé.
    */
    ro = (t_vec3){ ro.x / b_axis, ro.y / a_axis, ro.z / b_axis };
    rd = (t_vec3){ rd.x / b_axis, rd.y / a_axis, rd.z / b_axis };
    R /= b_axis;

    // coefficients quartiques (comme hit_torus)
    double dd = vec3_dot(rd, rd);
    double e = vec3_dot(ro, ro) - (R*R + 1.0);
    double f = vec3_dot(ro, rd);
    double four_R2 = 4.0 * R * R;

    a[0] = (e*e - four_R2 * (1.0 - ro.y*ro.y)) / (dd*dd);
    a[1] = (4.0*f*e + 2.0*four_R2 * ro.y*rd.y) / (dd*dd);
    a[2] = (2.0*dd*e + 4.0*f*f + four_R2 * rd.y*rd.y) / (dd*dd);
    a[3] = (4.0*dd*f) / (dd*dd);
}

double hit_ring(t_ray *ray, t_obj *obj)
{
    double coeffs[4];
    double roots[4];
    int n;

    if (!obj->scal || !obj->scal2 || !obj->scal3)
        return (INFINITY);
    compute_coeffs_one_ring(ray, obj, coeffs);
    n = solve_quartic(coeffs, roots);
    if (n == 0)
        return INFINITY;
    for (int i=0; i<n; i++)
        if (roots[i] > 0)
            return roots[i];
    return INFINITY;
}

t_vec3 ring_normal(t_obj *obj, t_vec3 hit_point)
{
    double a_axis = obj->scal3; // vertical
    double b_axis = obj->scal;  // radial
    double R      = obj->scal2; // grand rayon

    // === 1. Espace local ===
    t_vec3 u, v, w;
    w = vec3_normalized(obj->n);
    if (fabs(w.y) < 0.9)
        u = vec3_normalized(vec3_cross((t_vec3){0,1,0}, w));
    else
        u = vec3_normalized(vec3_cross((t_vec3){1,0,0}, w));
    v = vec3_cross(w, u);

    t_vec3 p = vec3_sub(hit_point, obj->pt);
    t_vec3 pl = {
        vec3_dot(p, u) / b_axis,
        vec3_dot(p, w) / a_axis,
        vec3_dot(p, v) / b_axis
    };

    // === 2. Normale géométrique (gradient dans espace scalé) ===
    double sumsq = vec3_dot(pl, pl);
    t_vec3 n_scaled = {
        4.0 * pl.x * (sumsq - (R/b_axis)*(R/b_axis) - 1.0),
        4.0 * pl.y * (sumsq - (R/b_axis)*(R/b_axis) - 1.0 + 2.0*(R/b_axis)*(R/b_axis)),
        4.0 * pl.z * (sumsq - (R/b_axis)*(R/b_axis) - 1.0)
    };

    // inverse transpose du scaling
    t_vec3 n_local = {
        n_scaled.x / b_axis,
        n_scaled.y / a_axis,
        n_scaled.z / b_axis
    };

    // === 3. Repasser dans l’espace monde ===
    t_vec3 geo_normal = {
        n_local.x * u.x + n_local.y * w.x + n_local.z * v.x,
        n_local.x * u.y + n_local.y * w.y + n_local.z * v.y,
        n_local.x * u.z + n_local.y * w.z + n_local.z * v.z
    };
    geo_normal = vec3_normalized(geo_normal);

    // === 4. Si pas de normal map ===
    if (!obj->normal_map_data)
        return geo_normal;

    // === 5. Base tangentielle ===
    t_vec3 tangent = vec3_cross(obj->n, geo_normal);
    if (vec3_norm(tangent) < 1e-6)
        tangent = u; // fallback
    tangent = vec3_normalized(tangent);
    t_vec3 bitangent = vec3_cross(geo_normal, tangent);

    // === 6. Coordonnées UV ===
    // u coord = angle autour du grand cercle
    double phi = atan2(pl.z, pl.x); 
    // v coord = angle dans la section elliptique
    double theta = atan2(pl.y * b_axis, (sqrt(pl.x*pl.x + pl.z*pl.z) - R/b_axis) * a_axis);

    double U = phi / (2.0 * M_PI) + 0.5;
    double V = theta / (2.0 * M_PI) + 0.5;

    t_normap normap;
    normap.u = U;
    normap.v = V;

    // === 7. Sample normal map ===
    t_vec3 map_normal = sample_normal_map(obj, normap.u, normap.v);

    // === 8. Appliquer perturbation ===
    return apply_normal_mapping(geo_normal, tangent, bitangent, map_normal);
}

// t_vec3 ring_normal(t_obj *obj, t_vec3 hit_point)
// {
//     double a_axis = obj->scal3; // vertical
//     double b_axis = obj->scal;  // radial
//     double R      = obj->scal2; // grand rayon

//     // 1. ramener le point dans l’espace local + scalé
//     t_vec3 p = vec3_sub(hit_point, obj->pt);

//     // base locale (même que dans compute_coeffs_one_ring)
//     t_vec3 u, v, w;
//     w = vec3_normalized(obj->n);
//     if (fabs(w.y) < 0.9)
//         u = vec3_normalized(vec3_cross((t_vec3){0,1,0}, w));
//     else
//         u = vec3_normalized(vec3_cross((t_vec3){1,0,0}, w));
//     v = vec3_cross(w, u);

//     t_vec3 pl = {
//         vec3_dot(p, u) / b_axis,
//         vec3_dot(p, w) / a_axis,
//         vec3_dot(p, v) / b_axis
//     };

//     // 2. normale du tore classique dans l’espace scalé
//     double sumsq = vec3_dot(pl, pl);
//     t_vec3 n_scaled = {
//         4.0 * pl.x * (sumsq - (R/b_axis)*(R/b_axis) - 1.0),
//         4.0 * pl.y * (sumsq - (R/b_axis)*(R/b_axis) - 1.0 + 2.0*(R/b_axis)*(R/b_axis)),
//         4.0 * pl.z * (sumsq - (R/b_axis)*(R/b_axis) - 1.0)
//     };

//     // 3. repasser dans espace original via inverse transpose du scaling
//     t_vec3 n_world_local = {
//         n_scaled.x / b_axis,
//         n_scaled.y / a_axis,
//         n_scaled.z / b_axis
//     };

//     // 4. repasser dans espace monde
//     t_vec3 n_world = {
//         n_world_local.x * u.x + n_world_local.y * w.x + n_world_local.z * v.x,
//         n_world_local.x * u.y + n_world_local.y * w.y + n_world_local.z * v.y,
//         n_world_local.x * u.z + n_world_local.y * w.z + n_world_local.z * v.z
//     };

//     return vec3_normalized(n_world);
// }
