#include "minirt.h"

int	fill_values_spot(void *rt, t_uipane *cur)
{
	t_light	*s;

	s = cur->light;
	putnbr_ui((t_env *)rt, 157, 92, s->color.r);
	putnbr_ui((t_env *)rt, 157, 122, s->color.g);
	putnbr_ui((t_env *)rt, 157, 152, s->color.b);
	putnbr_ui((t_env *)rt, 157, 182, s->pos.x);
	putnbr_ui((t_env *)rt, 157, 212, s->pos.y);
	putnbr_ui((t_env *)rt, 157, 242, s->pos.z);
	putnbr_ui((t_env *)rt, 157, 272, s->brightness);
	// putnbr_ui((t_env*)rt, 157, 242, s->index);
	// s->index a implementer
	return (0);
}
