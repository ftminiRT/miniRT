#include "minirt.h"

t_vec3 moebius_normal(t_obj *obj, t_vec3 hit_point, t_env *rt)
{
    t_vec3 geo_normal;
    t_vec3 tangent;
    t_vec3 bitangent;
    t_vec3 map_normal;
    t_normap normap;
    t_basis b;
    t_vec3 local_hit;
    double eps = 1e-6;
    
    b = make_basis(obj->n);
    t_vec3 rel = vec3_sub(hit_point, obj->pt);
    local_hit = world_to_local_vec(rel, b);
    
    // Récupérer les paramètres comme dans inside()
    double t = atan2(local_hit.y, local_hit.x);
    double s;
    
    if (fabs(sin(t / 2)) > eps)
        s = local_hit.z / sin(t / 2);
    else
        s = (local_hit.x / cos(t) - obj->scal) / cos(t / 2);
    
    // Dérivées partielles de la surface paramétrique
    // Point sur surface: P(t,s) = ((R + s*cos(t/2))*cos(t), (R + s*cos(t/2))*sin(t), s*sin(t/2))
    double R = obj->scal;
    double ct = cos(t);
    double st = sin(t);
    double ct2 = cos(t/2);
    double st2 = sin(t/2);
    
    // ∂P/∂t
    t_vec3 dP_dt = {
        -(R + s*ct2)*st - 0.5*s*st2*ct,
        (R + s*ct2)*ct - 0.5*s*st2*st,
        0.5*s*ct2
    };
    
    // ∂P/∂s  
    t_vec3 dP_ds = {
        ct2*ct,
        ct2*st,
        st2
    };
    
    // Normale = dP_dt × dP_ds
    geo_normal = vec3_cross(dP_dt, dP_ds);
    vec3_normalize(&geo_normal);
    
    // Transformer en coordonnées monde
    geo_normal = local_to_world_vec(geo_normal, b);
    
    if (!obj->normal_map_data || rt->basicrt)
        return (geo_normal);
    
    // Normal mapping
    tangent = dP_dt;
    tangent = local_to_world_vec(tangent, b);
    vec3_normalize(&tangent);
    bitangent = vec3_cross(geo_normal, tangent);
    vec3_normalize(&bitangent);
    
    normap.u = (t + M_PI) / (2.0 * M_PI);
    normap.v = (s / obj->max + 1.0) * 0.5;
    
    if (normap.u >= 1.0) normap.u -= 1.0;
    normap.v = fmax(0.0, fmin(1.0, normap.v));
    
    map_normal = sample_normal_map(obj, normap.u, normap.v);
    return (apply_normal_mapping(geo_normal, tangent, bitangent, map_normal));
}