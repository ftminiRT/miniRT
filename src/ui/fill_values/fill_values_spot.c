#include "minirt.h"

int	fill_values_spot(void *rt, t_uipane *cur)
{
	t_light	*s;

	s = cur->light;
	putstr_ui((t_env *)rt, 157, 92, dota(rt, s->color.r));
	putstr_ui((t_env *)rt, 157, 122, dota(rt, s->color.g));
	putstr_ui((t_env *)rt, 157, 152, dota(rt, s->color.b));
	putstr_ui((t_env *)rt, 157, 182, dota(rt, s->pos.x));
	putstr_ui((t_env *)rt, 157, 212, dota(rt, s->pos.y));
	putstr_ui((t_env *)rt, 157, 242, dota(rt, s->pos.z));
	putstr_ui((t_env *)rt, 157, 272, dota(rt, s->brightness));
	putstr_ui((t_env *)rt, 157, 302, ft_itoa(s->index));
	return (0);
}
