#include "minirt.h"

int	build_pane_color(void *rt, t_uipane *current)
{
	t_color	*color;

	(void)rt;
	if ((current->type == OT_DFT || current->type == OT_LIGHT)
		&& current->light)
		color = &current->light->color;
	else if (current->type >= OT_SPHERE && current->type <= OT_RING
		&& current->obj)
		color = &current->obj->color;
	else
		return (1);
	if (add_btn(setb((t_btn_data){&color->r, -STEP_COL, VEC0, UIT_COL_BTN},
				pt(106, 92), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&color->g, -STEP_COL, VEC0, UIT_COL_BTN},
				pt(106, 122), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&color->b, -STEP_COL, VEC0, UIT_COL_BTN},
				pt(106, 152), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&color->r, STEP_COL, VEC0, UIT_COL_BTN},
				pt(136, 92), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&color->g, STEP_COL, VEC0, UIT_COL_BTN},
				pt(136, 122), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&color->b, STEP_COL, VEC0, UIT_COL_BTN},
				pt(136, 152), BTNSZ), current))
		return (1);
	return (0);
}

static t_basis	get_local_basis(t_env *rt, t_uipane *current)
{
	t_basis	b;

	if (current->type >= OT_SPHERE && current->type <= OT_RING && current->obj)
	{
		build_local_basis(rt, &current->obj->local_basis);
		b = current->obj->local_basis;
	}
	else if (current->type == OT_DFT && current->cam)
	{
		build_local_basis(rt, &current->cam->local_basis);
		b = current->cam->local_basis;
	}
	else if (current->type == OT_LIGHT && current->light)
	{
		build_local_basis(rt, &current->light->local_basis);
		b = current->light->local_basis;
	}
	else
		b = (t_basis){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	return (b);
}

int	build_pane_pos(void *rt, t_uipane *current, t_vec3 *pos, int y)
{
	t_basis	b;
	double	step;

	step = STEP_POS;
	b = get_local_basis(rt, current);
	if (current->type == OT_LIGHT)
		step = STEP_SPOS;
	if (add_btn(setb((t_btn_data){pos, 0, vec3_scalmult(-step, b.w),
				UIT_MV_BTN}, pt(106, y), BTNSZ), current)
		|| add_btn(setb((t_btn_data){pos, 0, vec3_scalmult(-step, b.v),
				UIT_MV_BTN}, pt(106, y + 30), BTNSZ), current)
		|| add_btn(setb((t_btn_data){pos, 0, vec3_scalmult(-step, b.u),
				UIT_MV_BTN}, pt(106, y + 60), BTNSZ), current)
		|| add_btn(setb((t_btn_data){pos, 0, vec3_scalmult(step, b.w),
				UIT_MV_BTN}, pt(136, y), BTNSZ), current)
		|| add_btn(setb((t_btn_data){pos, 0, vec3_scalmult(step, b.v),
				UIT_MV_BTN}, pt(136, y + 30), BTNSZ), current)
		|| add_btn(setb((t_btn_data){pos, 0, vec3_scalmult(step, b.u),
				UIT_MV_BTN}, pt(136, y + 60), BTNSZ), current))
		return (1);
	return (0);
}

int	build_pane_dir(void *rt, t_uipane *current, t_vec3 *dir, int y)
{
	(void)rt;
	if (add_btn(setb((t_btn_data){dir, 0, (t_vec3){-STEP_ROT, 0, 0},
				UIT_ROT_BTN}, pt(106, y), BTNSZ), current)
		|| add_btn(setb((t_btn_data){dir, 0, (t_vec3){0, -STEP_ROT, 0},
				UIT_ROT_BTN}, pt(106, y + 30), BTNSZ), current)
		|| add_btn(setb((t_btn_data){dir, 0, (t_vec3){0, 0, -STEP_ROT},
				UIT_ROT_BTN}, pt(106, y + 60), BTNSZ), current)
		|| add_btn(setb((t_btn_data){dir, 0, (t_vec3){STEP_ROT, 0, 0},
				UIT_ROT_BTN}, pt(136, y), BTNSZ), current)
		|| add_btn(setb((t_btn_data){dir, 0, (t_vec3){0, STEP_ROT, 0},
				UIT_ROT_BTN}, pt(136, y + 30), BTNSZ), current)
		|| add_btn(setb((t_btn_data){dir, 0, (t_vec3){0, 0, STEP_ROT},
				UIT_ROT_BTN}, pt(136, y + 60), BTNSZ), current))
		return (1);
	return (0);
}

int	build_pane_mat(void *rt, t_uipane *current, int y)
{
	t_obj	*o;

	(void)rt;
	o = current->obj;
	if (add_btn(setb((t_btn_data){&o->shine, (double)1 / STEP_SH, VEC0, UIT_SH_BTN},
				pt(106, y), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->reflect, -STEP_RF, VEC0, UIT_01_BTN},
				pt(106, y + 30), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->shine, STEP_SH, VEC0, UIT_SH_BTN},
				pt(136, y), BTNSZ), current)
		|| add_btn(setb((t_btn_data){&o->reflect, STEP_RF, VEC0, UIT_01_BTN},
				pt(136, y + 30), BTNSZ), current))
		return (1);
	return (0);
}
