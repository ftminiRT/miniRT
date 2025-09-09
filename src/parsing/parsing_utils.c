/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:37:33 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 18:16:26 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	str_is_double(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!(ft_isdigit(str[i]) || str[i] == '.' || str[i] == '-'
				|| str[i] == '+'))
			return (0);
		i++;
	}
	return (i != 0);
}

static int	split_is_numeric(char **split)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!str_is_double(split[i]))
			return (0);
		i++;
	}
	return (1);
}

int	str_to_vec3(t_vec3 *vec, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (perror("Error :"), 1);
	if (count_arg(split) != 3 || !split_is_numeric(split))
		return (ft_free_split(split), 1);
	// printf("strings: {%s} {%s} {%s}\n", split[0], split[1], split[2]);
	vec->x = ft_atod(split[0]);
	vec->y = ft_atod(split[1]);
	vec->z = ft_atod(split[2]);
	// printf("doubles: {%f} {%f} {%f} \n", vec->x, vec->y, vec->z);
	ft_free_split(split);
	return (0);
}

int	str_to_colors(t_color *clr, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (perror("Error :"), 1);
	if (count_arg(split) != 3 || !split_is_numeric(split))
		return (ft_free_split(split), 1);
	clr->r = (unsigned char)ft_atoi(split[0]);
	clr->g = (unsigned char)ft_atoi(split[1]);
	clr->b = (unsigned char)ft_atoi(split[2]);
	ft_free_split(split);
	return (0);
}
