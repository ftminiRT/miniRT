#include "minirt.h"

// Fonction pour calculer la normale d'un objet au point d'intersection
t_vec3 get_normal(t_obj *obj, t_vec3 hit_point)
{
    t_vec3 normal;
    
    if (obj->type == OT_SPHERE)
    {
        normal = vec3_sub(hit_point, obj->sphere.center);
        vec3_normalize(&normal);
    }
    else if (obj->type == OT_PLANE)
    {
        normal = obj->plane.n;
    }
    else if (obj->type == OT_CYL)
    {
        // Pour un cylindre, calculer la normale selon la position
        t_vec3 axis_point = vec3_add(obj->cyl.center, 
                           vec3_scalmult(vec3_dot(vec3_sub(hit_point, obj->cyl.center), obj->cyl.n), obj->cyl.n));
        normal = vec3_sub(hit_point, axis_point);
        vec3_normalize(&normal);
    }
    else
        normal = (t_vec3){INFINITY, INFINITY, INFINITY};
    return normal;
}

// Fonction pour mélanger deux couleurs
t_color color_add(t_color c1, t_color c2)
{
    t_color result;
    result.r = (unsigned char)fmin(255, (int)c1.r + (int)c2.r);
    result.g = (unsigned char)fmin(255, (int)c1.g + (int)c2.g);
    result.b = (unsigned char)fmin(255, (int)c1.b + (int)c2.b);
    return result;
}

// Fonction pour multiplier une couleur par un facteur
t_color color_scale(t_color c, double factor)
{
    t_color result;
    result.r = (unsigned char)fmin(255, (int)(c.r * factor));
    result.g = (unsigned char)fmin(255, (int)(c.g * factor));
    result.b = (unsigned char)fmin(255, (int)(c.b * factor));
    return result;
}

// Fonction principale d'éclairage adaptée à vos structures
t_color calculate_lighting(t_env *rt, t_obj *obj, t_vec3 hit_point, t_vec3 ray_dir)
{
    t_vec3 normal = get_normal(obj, hit_point);
    t_vec3 view_dir = vec3_scalmult(-1.0, ray_dir);
    vec3_normalize(&view_dir);
    
    // Couleur de base de l'objet
    t_color base_color = obj->color;
    
    // 1. COMPOSANTE AMBIANTE
    // Utilise rt->ambient.brightness comme intensité et rt->ambient.color comme couleur
    t_color ambient_light = color_scale(rt->ambient.color, rt->ambient.brightness);
    t_color ambient = {
        (unsigned char)((base_color.r * ambient_light.r) / 255),
        (unsigned char)((base_color.g * ambient_light.g) / 255),
        (unsigned char)((base_color.b * ambient_light.b) / 255)
    };
    
    // 2. COMPOSANTE DIFFUSE ET SPÉCULAIRE (lumière spot)
    
    // Direction vers la lumière
    t_vec3 light_dir = vec3_sub(rt->spot.pos, hit_point);
    double light_distance = vec3_norm(light_dir);
    vec3_normalize(&light_dir);
    
    // Test d'ombre simple
    t_ray shadow_ray;
    shadow_ray.pt = vec3_add(hit_point, vec3_scalmult(0.001, normal)); // Petit décalage
    shadow_ray.dir = light_dir;
    shadow_ray.hit = INFINITY;
    
    t_obj *shadow_obj = compute_intersections(rt, &shadow_ray);
    int in_shadow = (shadow_obj && shadow_ray.hit < light_distance - 0.001);
    
    t_color final_color = ambient;
    
    if (!in_shadow)
    {
        // Calcul diffus (Lambert)
        double diff = fmax(0.0, vec3_dot(normal, light_dir));
        
        // Calcul spéculaire (Phong)
        t_vec3 reflect_dir = vec3_sub(vec3_scalmult(2.0 * vec3_dot(normal, light_dir), normal), light_dir);
        vec3_normalize(&reflect_dir);
        double spec = pow(fmax(0.0, vec3_dot(reflect_dir, view_dir)), 32.0);
        
        // Atténuation avec la distance
        double attenuation = 1.0 / (1.0 + 0.09 * light_distance + 0.032 * light_distance * light_distance);
        
        // Couleur de la lumière spot
        t_color spot_light = color_scale(rt->spot.color, rt->spot.brightness * attenuation);
        
        // Composante diffuse
        t_color diffuse = {
            (unsigned char)((base_color.r * spot_light.r * diff) / 255),
            (unsigned char)((base_color.g * spot_light.g * diff) / 255),
            (unsigned char)((base_color.b * spot_light.b * diff) / 255)
        };
        
        // Composante spéculaire (reflet blanc)
        t_color specular = color_scale(spot_light, spec * 0.5); // Facteur 0.5 pour ne pas être trop fort
        
        // Combiner toutes les composantes
        final_color = color_add(final_color, diffuse);
        final_color = color_add(final_color, specular);
    }
    
    return final_color;
}

// Version simplifiée pour tester d'abord
t_color simple_lighting(t_env *rt, t_obj *obj, t_vec3 hit_point)
{
    t_vec3 normal = get_normal(obj, hit_point);
    t_color base_color = obj->color;
    
    // Direction vers la lumière
    t_vec3 light_dir = vec3_sub(rt->spot.pos, hit_point);
    vec3_normalize(&light_dir);
    
    // Facteur diffus
    double diff = fmax(0.0, vec3_dot(normal, light_dir));
    
    // Combinaison simple : ambient + diffus
    double total_light = rt->ambient.brightness + diff * rt->spot.brightness;
    total_light = fmin(1.0, total_light); // Clamp à 1.0
    
    t_color result = color_scale(base_color, total_light);
    
    return result;
}