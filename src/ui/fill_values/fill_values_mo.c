#include "minirt.h"

int	fill_values_mo(void *rt, t_uipane *cur)
{
	t_obj	*o;

	o = cur->obj;
	putstr_ui((t_env *)rt, 157, 92, dota(rt, o->color.r));
	putstr_ui((t_env *)rt, 157, 122, dota(rt, o->color.g));
	putstr_ui((t_env *)rt, 157, 152, dota(rt, o->color.b));
	putstr_ui((t_env *)rt, 157, 182, dota(rt, o->pt.x));
	putstr_ui((t_env *)rt, 157, 212, dota(rt, o->pt.y));
	putstr_ui((t_env *)rt, 157, 242, dota(rt, o->pt.z));
	putstr_ui((t_env *)rt, 157, 272, dota(rt, o->n.x));
	putstr_ui((t_env *)rt, 157, 302, dota(rt, o->n.y));
	putstr_ui((t_env *)rt, 157, 332, dota(rt, o->n.z));
	putstr_ui((t_env *)rt, 157, 362, dota(rt, o->scal));
	putstr_ui((t_env *)rt, 157, 392, dota(rt, o->max));
	putstr_ui((t_env *)rt, 157, 422, dota(rt, o->shine));
	putstr_ui((t_env *)rt, 157, 452, dota(rt, o->reflect));
	return (0);
}
