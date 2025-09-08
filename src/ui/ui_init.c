/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-02 11:25:52 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-02 11:25:52 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define PATH_CONE "./assets/ui_assets/xpm/ui_cone.xpm"
#define PATH_CYL "./assets/ui_assets/xpm/ui_cylinder.xpm"
#define PATH_DFT "./assets/ui_assets/xpm/ui_default.xpm"
#define PATH_LIGHT "./assets/ui_assets/xpm/ui_lights.xpm"
#define PATH_MOEB "./assets/ui_assets/xpm/ui_moeb.xpm"
#define PATH_PLANE "./assets/ui_assets/xpm/ui_plane.xpm"
#define PATH_RING "./assets/ui_assets/xpm/ui_ring.xpm"
#define PATH_SP "./assets/ui_assets/xpm/ui_sphere.xpm"
#define PATH_TOR "./assets/ui_assets/xpm/ui_tore.xpm"

int	set_pane_img(t_env *rt, t_objtype type, char *path)
{
	void	*new_img;
	int		width;
	int		height;

	width = UI_WIDTH;
	height = UI_HEIGHT;
	height = UI_HEIGHT;
	width = UI_WIDTH;
	printf("loading file : [%s] w:%d h:%d t:%d\n", path, width, height, type);
	new_img = mlx_xpm_file_to_image(rt->mlx.mlx, path, &width, &height);
	if (!new_img)
		return (write(2, "miniRT : error while loading xpm img\n", 38), 1);
	rt->ui.pane_img[type] = new_img;
	return (0);	
}

int	init_pane_img(t_env *rt)
{
	t_objtype	i;
	char		*path[OBJTYPENUMBER];

	path[OT_CONE] = PATH_CONE;
	path[OT_CYL] = PATH_CYL;
	path[OT_DFT] = PATH_DFT;
	path[OT_LIGHT] = PATH_LIGHT;
	path[OT_MOEB] = PATH_MOEB;
	path[OT_PLANE] = PATH_PLANE;
	path[OT_RING] = PATH_RING;
	path[OT_SPHERE] = PATH_SP;
	path[OT_TORE] = PATH_TOR;

	i = OT_DFT;
	while (1)
	{
		if (set_pane_img(rt, i, path[i]))
			return (1);
		i = (i + 1) % OBJTYPENUMBER;
		if (i == OT_DFT)
			break ;
	}
	return (0);
}

t_items *add_new_button(void *value, double factor, t_uipt pos, t_uipt scale)
{
	t_items	*new;

	new = malloc(sizeof(t_items));
	if (!new)
		return (NULL);
	new->btn.factor = factor;
	new->btn.value = value;
	new->pos.x = pos.x;
	new->pos.y = pos.y;
	new->scale.x = scale.x;
	new->scale.y = scale.y;
	return (new);
}

int	add_default_buttons(t_env *rt)
{
	rt->ui.dft_itms = add_new_button(&rt->ambient.brightness, 0.1, (t_uipt){100,100}, (t_uipt){30,30});
	if (!rt->ui.dft_itms)
		return (1);
	putpixel_ui(100, 100, rt, (t_color){255, 0, 0});
	return (0);
}

int ui_init(t_env *rt)
{
	init_pane_builders(rt);
	if (init_pane_img(rt))
		return (1);
	if (init_ui_panes(rt))
		return (1);
	if (add_default_buttons(rt))
		return (1);
	display_ui(rt);
	return (0);
}