#include "minirt.h"

void	init_pane_builders(t_env *rt)
{
	rt->ui.build_pane[OT_DFT] = build_pane_dft;
	rt->ui.build_pane[OT_CONE] = build_pane_co;
	rt->ui.build_pane[OT_CYL] = build_pane_cyl;
	rt->ui.build_pane[OT_MOEB] = build_pane_mo;
	rt->ui.build_pane[OT_PLANE] = build_pane_pl;
	rt->ui.build_pane[OT_RING] = build_pane_ri;
	rt->ui.build_pane[OT_SPHERE] = build_pane_sp;
	rt->ui.build_pane[OT_TORE] = build_pane_to;
	rt->ui.build_pane[OT_LIGHT] = build_pane_spot;
}

void	init_pane_fillers(t_env *rt)
{
	rt->ui.fill_values[OT_DFT] = fill_values_dft;
	rt->ui.fill_values[OT_CONE] = fill_values_co;
	rt->ui.fill_values[OT_CYL] = fill_values_cy;
	rt->ui.fill_values[OT_MOEB] = fill_values_mo;
	rt->ui.fill_values[OT_PLANE] = fill_values_pl;
	rt->ui.fill_values[OT_RING] = fill_values_ri;
	rt->ui.fill_values[OT_SPHERE] = fill_values_sp;
	rt->ui.fill_values[OT_TORE] = fill_values_to;
	rt->ui.fill_values[OT_LIGHT] = fill_values_spot;
}

