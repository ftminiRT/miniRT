
#include "minirt.h"

t_obj	*clicked_object(t_env *rt, int x, int y)
{
	t_ray	ray;

	compute_ray(rt, &ray, x, y);
	return (compute_intersections(rt, &ray));
}

void	modify_scal(t_select *s, double step)
{
	if (s->type == AMB && s->amb)
		s->amb->brightness += step / 10;
	if (s->type == SPOT && s->spot)
		s->spot->brightness += step / 10;
	if (s->type == OBJ && s->obj)
		s->obj->scal += step;
	if (s->type == CAM && s->cam)
		s->cam->fov += step;
}

static bool is_in_window(int x, int y)
{
	return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

static bool useful_hook(int bt)
{
	if (bt == SCROLL_UP || bt == SCROLL_DOWN)
		return (true);
	return (false);
}

int	mouse_hook(int bt, int x, int y, t_env *rt)
{
	t_obj	*clicked;
	double	step;

	step = 1;
	if (bt == LEFT_CLIC && is_in_window(x, y))
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
            }
		}
	}
	if (bt == SCROLL_UP)
		modify_scal(&rt->selected, step);
	if (bt == SCROLL_DOWN)
		modify_scal(&rt->selected, -step);
	if (useful_hook(bt))
		ray_trace(rt);
	return (1);
}
