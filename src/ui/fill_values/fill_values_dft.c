#include "minirt.h"

int    fill_values_dft(void *rt, t_uipane *cur)
{
    t_light *a;
    t_cam   *c;
    t_env   *e;

    e = (t_env*)rt;
    a = cur->light;
    c = cur->cam;
    putstr_ui((t_env*)rt, 157, 92, dota(rt, a->color.r));
    putstr_ui((t_env*)rt, 157, 122, dota(rt, a->color.g));
    putstr_ui((t_env*)rt, 157, 152, dota(rt, a->color.b));
    putstr_ui((t_env*)rt, 157, 182, dota(rt, a->brightness));
    putstr_ui((t_env*)rt, 157, 242, dota(rt, c->pos.x));
    putstr_ui((t_env*)rt, 157, 272, dota(rt, c->pos.y));
    putstr_ui((t_env*)rt, 157, 302, dota(rt, c->pos.z));
    putstr_ui((t_env*)rt, 157, 332, dota(rt, c->dir.x));
    putstr_ui((t_env*)rt, 157, 362, dota(rt, c->dir.y));
    putstr_ui((t_env*)rt, 157, 392, dota(rt, c->dir.z));
    putstr_ui((t_env*)rt, 157, 422, dota(rt, c->fov));
    return (0);
}