#include "minirt.h"
#include "ui.h"

static void	display_frames(t_env *rt)
{
	int	i;
	int	j;
	int offset;

	offset = 3;
	i = 0;
	j = 0;
	while (j < UI_HEIGHT)
	{
		while (i < UI_WIDTH)
		{
			if (i <= offset || i >= UI_WIDTH - offset || j <= offset || j >= UI_HEIGHT - offset)
				putpixel_ui(i, j, rt, (t_color){i, 160, 255});
			i++;
		}
		i = 0;
		j++;
	}
}

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
	
	display_frames(rt);
	put_rgb_picker(rt, 20, 20);
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.ui.img, WIDTH, 0);
}