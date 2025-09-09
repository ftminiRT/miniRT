#include "minirt.h"

int    fill_values_mo(void *rt, t_uipane *cur)
{
    t_obj   *cy;

    if (cur->type == OT_CYL && cur->obj)
        cy = cur->obj;
    else
        return (1);
    putstr_ui((t_env*)rt, 166, 272, "nsm le mere");
    return (0);
}