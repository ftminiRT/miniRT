
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
        s->amb->brightness += step / 10;
    if (s->type == SPOT)
        s->spot->brightness += step / 10;
    if (s->type == OBJ)
        s->obj->scal += step;
    if (s->type == CAM)
        s->cam->fov += step;
}

static t_uipane *get_current(t_env *rt, t_obj *clicked)
{
    t_uipane *current;

    current = rt->ui.stock;
    while (current && current->obj != clicked)
        current = current->next;
    return (current);
}

int	mouse_hook(int bt, int x, int y, t_env *rt)
{
    t_obj   *clicked;
    double  step = 1;

    if (bt == LEFT_CLIC)
    {
        if (x >= WIDTH)
            click_ui(x - WIDTH, y, rt);
        else
        {
            clicked = clicked_object(rt, x, y);
            if (clicked)
            {
                rt->selected.type = OBJ;
                rt->selected.obj = clicked;
                rt->ui.current = get_current(rt, clicked);
            }
        }
    }
    if (bt == SCROLL_UP)
        modify_scal(&rt->selected, step);
    if (bt == SCROLL_DOWN)
        modify_scal(&rt->selected, -step);
    display_ui(rt);
    ray_trace(rt);
    return (1);
}
