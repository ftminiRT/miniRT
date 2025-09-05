
#include "minirt.h"

int	sign_str(char **str)
{
	if (**str == '-' || **str == '+')
	{
		(*str)++;
		if (**str == '-')
			return (-1);
	}
	return (1);
}

double	ft_atod(char *str)
{
	double	nb[2];
	double	power;
	char	**split;
	int		len;
	int		sign;

	sign = sign_str(&str);
	split = ft_split(str, '.');
	if (!split)
		return (perror("miniRT"), 0);
	nb[0] = ft_atoi(split[0]);
	if (!split[1])
		return (ft_free_split(split), nb[0]);
	nb[1] = ft_atoi(split[1]);
	len = ft_strlen(split[1]);
	ft_free_split(split);
	power = 1;
	while (len)
	{
		power = power * 10;
		len--;
	}
	return (nb[0] * sign + (nb[1] / power) * sign);
}
