#include "minirt.h"
#include "ui.h"

void	display_color_frame(t_env *rt, void *img, t_objtype type)
{
	t_color *clr;

	(void)	img;
	if (type == OT_LIGHT || type == OT_DFT)
		clr = &rt->ui.current->light->color;
	else
		clr = &rt->ui.current->obj->color;
	printf("r:%d g:%d b:%d\n", clr->r, clr->g, clr->b);
}

void	wipe_ui_values(t_env *rt, void *img)
{
	int	i;
	int	j;

	(void) rt;
	j = 79;
	while (j < 495)
	{
		i = 149;
		while (i < 200)
		{
			putpixel_ui_img(i, j, (t_color){0,0,0}, img);
			printf("%d, %d\n", i, j);
			i++;
		}
		j++;
	}

}

void	ui_print_values(t_env *rt, void *img)
{
	t_objtype type;

	type = rt->ui.current->type;
	display_color_frame(rt, img, type);
	wipe_ui_values(rt, img);
	//faire un tableau de fonction pour chaque type de fenetre
}

void	display_ui(t_env *rt)
{	
	void	*img;

	img = rt->ui.pane_img[rt->ui.current->type];
	ui_print_values(rt, img);
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, img, WIDTH, 0);
}