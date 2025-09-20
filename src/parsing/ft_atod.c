/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:54:32 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:54:32 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sign_str(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
		sign = -1;
	if (**str == '-' || **str == '+')
		(*str)++;
	return (sign);
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
		return (ft_free_split(split), nb[0] * sign);
	nb[1] = ft_atoi(split[1]);
	len = ft_strlen(split[1]);
	ft_free_split(split);
	power = 1;
	while (len)
	{
		power = power * 10;
		len--;
	}
	return ((nb[0] + (nb[1] / power)) * sign);
}
