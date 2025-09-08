#include "minirt.h"


int	build_pane_events(void *rt, t_uipane *current)
{
	t_cam	*c;
	t_light	*a;
	t_items *i;
	int		step = 5;

	i = &current->itms;
	c = current->cam;
	a = current->light;
	if (add_btn(setb(&a->color.r, -step, pt(106, 92), BTNSZ), i) ||
		add_btn(setb(&c->fov, step, pt(136, 422), BTNSZ), i))
		return (1);
	return (0);

}