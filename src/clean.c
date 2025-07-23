#include "minirt.h"

int	clear_mlx(t_env *rt)
{
	mlx_destroy_window(rt->mlx.mlx, rt->mlx.win);
	mlx_destroy_image(rt->mlx.mlx, rt->mlx.img);
	mlx_destroy_display(rt->mlx.mlx);
	free(rt->mlx);
	return (1);
}
