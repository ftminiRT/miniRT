#include "minirt.h"

void	putpixel(int x, int y, t_env *rt, t_color c)
{
	int	*iimg_addr;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	iimg_addr = (int *)rt->mlx.img.addr;
	iimg_addr[x + y * WIDTH] = (c.r << 16) | (c.g << 8) | c.b;
}
