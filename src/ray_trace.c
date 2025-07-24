#include "minirt.h"

t_obj    *compute_intersections(t_env *rt, t_ray *ray)
{
    t_list_obj  *objs;
    double      t;
    t_obj       *closest;

    t = INFINITY;
    closest = NULL;
    objs = rt->objects;
    while (objs)
    {
        if (objs->obj.type == OT_PLANE && hit_plane(ray, objs->obj.plane))
        {
                printf("j'ai hit le plan\n");
            if (0 < ray->hit && ray->hit < t)
            {
                t = ray->hit;
                printf("j'ai hit le plan nsgm\n");
                closest = &objs->obj;
            }
        }

        if (objs->obj.type == OT_SPHERE && hit_sphere(ray, objs->obj.sphere))
        {
            printf("sphere_hit %f\n", ray->hit);
            if (0 < ray->hit && ray->hit < t)
            {
                t = ray->hit;
                closest = &objs->obj;
            }
        }
        if (objs->obj.type == OT_CYL && hit_cylinder(ray, objs->obj.cyl))
        {
            if (0 < ray->hit && ray->hit < t)
            {
                                printf("j'ai hit le cyl\n");
                t = ray->hit;
                                printf("j'ai hit le cyl et je refresh closest\n");

                closest = &objs->obj;
            }
        }        
        objs = objs->next;
    }
    return (closest);
}


void    ray_trace(t_env *rt)
{
    t_ray       ray;
    t_obj       *hitted;
    int         i;
    int         j;

    j = -1;
    hitted = NULL;
    ray.pt = rt->cam.pos;
    while (++j < HEIGHT)
    {
        i = -1;
        while (++i < WIDTH)
        {
            ray.dir = vec3_add(
                vec3_scalmult(rt->cam.fov * (i - (WIDTH / 2)), vec3_right()),
                vec3_scalmult(rt->cam.fov * ((HEIGHT / 2) - j), vec3_up()));
            vec3_rotate(&ray.dir, rt->cam.dir);
            vec3_normalize(&ray.dir);
            ray.hit = 0;
            hitted = compute_intersections(rt, &ray);
            if (hitted)
            {
                printf("oui effectivement j'ai hit %d aux coordonnees %d %d\n", hitted->type, i, j);
                putpixel(i, j, rt, hitted->color);
            }
            hitted = NULL;
        }
    }
    printf("la bite\n");
    mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.img.img, 0, 0);
}