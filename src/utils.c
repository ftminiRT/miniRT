#include "minirt.h"

int	swapd(double *a, double *b)
{
	double	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
	return (1);
}

int	dblsgn(double x)
{
	if (x < -EPSILON)
		return (-1);
	return (x > EPSILON);
}
