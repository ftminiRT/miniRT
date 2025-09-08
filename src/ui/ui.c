#include "minirt.h"
#include "ui.h"

static void	put_rgb_picker(t_env *rt, int x, int y)
{
	int	i;
	int j;

	i = 0;
	while (i < 3)
	{
		j = 30;
		while (j < 150)
		{
			putpixel_ui(x + j, y, rt, (t_color){160, 160, 160});
			putpixel_ui(x + j, y + 1, rt, (t_color){160, 160, 160});
			j++;
		}
		i++;
		y += 22;
	}
}

void	display_ui(t_env *rt)
{	
	void	*img;
	img = rt->ui.pane_img[rt->ui.current->type];
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, img, WIDTH, 0);
}