#include "minirt.h"

void	handle_exit(int kc, t_env *rt)
{
	if (kc == KEY_ESC)
	{
		mrt_cleaner(rt);
		exit(1);
	}
}

void	handle_selection(int kc, t_env *rt)
{
	if (kc == KEY_C)
		rt->selected.type = CAM;
	if (kc == KEY_A)
		rt->selected.type = AMB;
	if (kc == KEY_S)
	{
		rt->selected.type = SPOT;
		if (!rt->selected.spot)
			rt->selected.spot = &rt->spot;
		else if (rt->selected.spot->next)
			rt->selected.spot = rt->selected.spot->next;
		else
			rt->selected.spot = &rt->spot;
	}
}

void	handle_movement(int kc, t_env *rt, double step, t_vec3 fwd)
{
	t_vec3	up;
	t_vec3	right;

	up = (t_vec3){0, 1, 0};
	right = vec3_normalized(vec3_cross(fwd, up));
	if (kc == KEY_LEFT)
		move_selected(rt, vec3_scalmult(-step, right));
	if (kc == KEY_RIGHT)
		move_selected(rt, vec3_scalmult(step, right));
	if (kc == KEY_UP)
		move_selected(rt, vec3_scalmult(step, up));
	if (kc == KEY_DOWN)
		move_selected(rt, vec3_scalmult(-step, up));
	if (kc == KEY_PLUS)
		move_selected(rt, vec3_scalmult(step, fwd));
	if (kc == KEY_MINUS)
		move_selected(rt, vec3_scalmult(-step, fwd));
}

void	handle_rotation(int kc, t_env *rt, double step)
{
	if (rt->selected.type == CAM)
		rot_cam(kc, rt, step);
	else
		rot_obj(kc, rt, step);
}

void	handle_object_mod(int kc, t_env *rt, double step)
{
	if (rt->selected.type == OBJ && rt->selected.obj->type == OT_RING
		&& kc == KEY_Q)
		rt->selected.obj->scal3 -= 1;
	if (rt->selected.type == OBJ && rt->selected.obj->type == OT_RING
		&& kc == KEY_W)
		rt->selected.obj->scal3 += 1;
	if (rt->selected.type != OBJ || !rt->selected.obj)
		return ;
	if (rt->selected.obj->type == OT_MOEB && kc == KEY_MINUS2)
		rt->selected.obj->max -= step / 10;
	if (rt->selected.obj->type == OT_MOEB && kc == KEY_PLUS2)
		rt->selected.obj->max += step / 10;
	if ((rt->selected.obj->type == OT_RING
		|| rt->selected.obj->type == OT_TORE
		|| rt->selected.obj->type == OT_CYL)
		&& kc == KEY_MINUS2)
		rt->selected.obj->scal2 -= step;
	if ((rt->selected.obj->type == OT_RING
		|| rt->selected.obj->type == OT_TORE
		|| rt->selected.obj->type == OT_CYL)
		&& kc == KEY_PLUS2)
		rt->selected.obj->scal2 += step;
	if (rt->selected.type == OBJ && kc == KEY_X)
		rt->selected.obj->checkered = !rt->selected.obj->checkered;
}
