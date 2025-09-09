#include "minirt.h"

char	*dota(t_env *rt, double n)
{
	char	*buf;

	buf = malloc(64);
	if (!buf)
	{
		mega_clean(rt);
		exit(1);
	}
	snprintf(buf, 64, "%.2f", n);
	return (buf);
}
