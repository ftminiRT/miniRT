
#include "minirt.h"

t_obj   *clicked_object(t_env *rt, int x, int y)
{
    t_ray   ray;

    compute_ray(rt, &ray, x, y);
    return(compute_intersections(rt, &ray));
}

void    modify_scal(t_select *s, double step)
{
    if (s->type == AMB)
        s->amb->brightness += step;
    if (s->type == SPOT)
        s->spot->brightness += step;
    if (s->type == OBJ)
        s->obj->scal += step;
    if (s->type == CAM)
        s->cam->fov += step;
}

int	mouse_hook(int bt, int x, int y, t_env *rt)
{
    t_obj   *clicked;
    double  step = 1;

    if (bt == LEFT_CLIC)
    {
        clicked = clicked_object(rt, x, y);
        if (clicked)
        {
            rt->selected.type = OBJ;
            rt->selected.obj = clicked;
        }
    }
    if (bt == SCROLL_UP)
        modify_scal(&rt->selected, step);
    if (bt == SCROLL_DOWN)
        modify_scal(&rt->selected, -step);
    ray_trace(rt);
    return (1);
}
