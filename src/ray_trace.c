#include "minirt.h"

t_obj    *compute_intersections(t_env *rt, t_ray *ray)
{
    t_obj       *objs;
    double      closest_t;
    double      t;
    t_obj       *closest;

    closest_t = INFINITY;
    t = INFINITY;
    closest = NULL;
    objs = rt->objects;
    while (objs)
    {
        t = rt->hit_object[objs->type](ray, objs);
        if (0 < t && t < closest_t)
        {
            closest_t = t;
            closest = objs;
        }
        objs = objs->next;
    }
    if (closest)
        ray->hit = closest_t;
    return (closest);
}

t_vec3 camera_transform(t_vec3 dir_local, t_vec3 cam_dir)
{
    t_vec3 forward = cam_dir;
    vec3_normalize(&forward);
    
    // Choisir un vecteur up de référence
    t_vec3 up_ref = (fabs(forward.y) > 0.99) ? (t_vec3){0, 0, 1} : (t_vec3){0, 1, 0};

    // Calculer le vecteur right (droite)
    t_vec3 right = vec3_cross(forward, up_ref);
    vec3_normalize(&right);
    
    // Calculer le vecteur up réel
    t_vec3 up = vec3_cross(right, forward);
    vec3_normalize(&up);

    // Transformation : right=X, up=Y, forward=Z dans l'espace caméra
    t_vec3 world_dir;
    world_dir.x = dir_local.x * right.x + dir_local.y * up.x + dir_local.z * forward.x;
    world_dir.y = dir_local.x * right.y + dir_local.y * up.y + dir_local.z * forward.y;
    world_dir.z = dir_local.x * right.z + dir_local.y * up.z + dir_local.z * forward.z;
    
    return world_dir; // Pas besoin de normaliser ici, c'est fait après
}
// Votre fonction ray_trace modifiée
void    ray_trace(t_env *rt)
{
    t_ray       ray;
    t_obj       *hitted;
    int         i;
    int         j;
    t_obj       *objs;

    j = -1;
    hitted = NULL;
    ray.pt = rt->cam.pos;
    vec3_normalize(&rt->cam.dir);
    
    // Normaliser les normales des objets
    objs = rt->objects;
    while(objs)
    {
        if (objs->type == OT_PLANE)
            vec3_normalize(&objs->n);
        if (objs->type == OT_CYL)
            vec3_normalize(&objs->n);
        objs = objs->next;
    }

    int total_pixels = 0;
    int lit_pixels = 0;
    
    while (++j < HEIGHT)
    {
        i = -1;
        while (++i < WIDTH)
        {
            ray.pt = rt->cam.pos;

            double aspect_ratio = (double)WIDTH / (double)HEIGHT;
            double fov_rad = rt->cam.fov * M_PI / 180.0;

            double px = (2 * ((i + 0.5) / (double)WIDTH) - 1) * tan(fov_rad / 2) * aspect_ratio;
            double py = (1 - 2 * ((j + 0.5) / (double)HEIGHT)) * tan(fov_rad / 2);

            t_vec3 dir_local = (t_vec3){px, py, 1};

            ray.dir = camera_transform(dir_local, rt->cam.dir);
            vec3_normalize(&ray.dir);

            ray.hit = INFINITY;
            hitted = compute_intersections(rt, &ray);
            
            total_pixels++;
            
            if (hitted)
            {
                lit_pixels++;
                
                // Calculer le point d'intersection
                t_vec3 hit_point = vec3_add(ray.pt, vec3_scalmult(ray.hit, ray.dir));
                
                // Calculer l'éclairage - COMMENCEZ PAR simple_lighting
                t_color lit_color = simple_lighting(rt, hitted, hit_point);
                
                putpixel(i, j, rt, lit_color);
            }
            else
            {
                // Couleur de fond
                t_color bg_color = {0, 0, 0};
                putpixel(i, j, rt, bg_color);
            }
        }
    }
    
    printf("Pixels total: %d, éclairés: %d\n", total_pixels, lit_pixels);
    mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.img.img, 0, 0);
}