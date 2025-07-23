#include "minirt.h"

void	putpixel(int x, int y, t_env *rt, t_color c)
{
	int	*iimg_addr;

	if (x + y * HEIGHT > WIDTH * HEIGHT || x > WIDTH - 1 || y > HEIGHT - 1 || x < 0 || y < 0)
		return ;
	iimg_addr = (int *)rt->mlx.img.addr;
	iimg_addr[x + y * WIDTH] = c.r * 65536 + c.g * 256 + c.b;
	rt->mlx.img.addr = (char *)iimg_addr;
}
