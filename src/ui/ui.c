/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 14:31:33 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 14:31:33 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ui.h"

void	auto_render_fill(t_env *rt, t_color clr)
{
	t_uipt	pos;
	int		i;
	int		j;

	pos.x = 132;
	pos.y = 4;
	i = 0;
	j = 0;
	while (j < 26)
	{
		while (i < 26)
		{
			if ((j >= 0 && j < 2) || (i >= 0 && i < 2)
				|| (j > 23 && j < 26) || (i > 23 && i < 26))
			{
				putpixel_ui_img(i + pos.x, j + pos.y, clr,
					rt->ui.pane_img[rt->ui.current->type]);
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	display_color_frame(t_env *rt, void *img, t_objtype type)
{
	t_color	clr;
	int		i;
	int		j;

	(void)img;
	if (type == OT_LIGHT || type == OT_DFT)
		clr = rt->ui.current->light->color;
	else
		clr = rt->ui.current->obj->color;
	i = 14;
	while (i < 55)
	{
		j = 80;
		while (j < 148)
		{
			putpixel_ui_img(i, j, clr, img);
			j++;
		}
		i++;
	}
}

void	wipe_ui_values(t_env *rt, void *img)
{
	int	i;
	int	j;

	(void)rt;
	j = 79;
	while (j < 495)
	{
		i = 149;
		while (i < 200)
		{
			putpixel_ui_img(i, j, (t_color){0, 0, 0}, img);
			i++;
		}
		j++;
	}
}

void	ui_print_values(t_env *rt, void *img)
{
	t_objtype	type;

	type = rt->ui.current->type;
	display_color_frame(rt, img, type);
	wipe_ui_values(rt, img);
	if (rt->render)
		auto_render_fill(rt, (t_color){0, 255, 100});
	else
		auto_render_fill(rt, (t_color){255, 255, 255});
}

void	display_ui(t_env *rt)
{
	void	*img;

	if (!rt->ui_set)
		return ;
	img = rt->ui.pane_img[rt->ui.current->type];
	ui_print_values(rt, img);
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, img, WIDTH, 0);
	rt->ui.fill_values[rt->ui.current->type](rt, rt->ui.current);
}
