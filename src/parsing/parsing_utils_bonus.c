/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-29 11:57:56 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-08-29 11:57:56 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_shine(t_obj *new, char *arg)
{
	if (new->shine)
		return (0);
	if (!str_is_double(arg))
		return (1);
	new->shine = ft_atod(arg);
	if (new->shine <= 0)
		return (1);
	return (0);
}

int	set_texture(t_obj *new, char *arg)
{
	printf("parsing texture:[%s]\n", arg);
	if (new->texture_filename)
		return (1);
	if (access(arg, F_OK))
		return (1);
	new->texture_filename = ft_strdup(arg);
	if (!new->texture_filename)
		return (1);
	return (0);
}

int	set_normal_map(t_obj *new, char *arg)
{
	printf("parsing normap:[%s]\n", arg);
	if (new->normal_map_filename)
		return (1);
	if (access(arg, F_OK))
		return (1);
	new->normal_map_filename = ft_strdup(arg);
	if (!new->normal_map_filename)
		return (1);
	return (0);
}

int	set_reflect(t_obj *new, char *arg)
{
	if (!str_is_double(arg))
		return (1);
	new->reflect = ft_atod(arg);
	if (new->reflect < 0.0 || new->reflect > 1.0)
		return (1);
	return (0);
}

int	set_bonus_attributes(char **args, t_env *rt, t_obj *new)
{
	int	i;

	(void)rt;
	i = 0;
	while (args[i])
	{
		if (args[i][ft_strlen(args[i]) - 1] == '\n')
			args[i][ft_strlen(args[i]) - 1] = 0;
		if (!ft_strncmp(args[i], "s:", 2) && set_shine(new, args[i] + 2))
			return (1);
		if (!ft_strncmp(args[i], "t:", 2))
		{
			printf("%d %s\n", __LINE__, __FILE__);
			if (!ft_strncmp(args[i] + 2, "checkered", 10))
				new->checkered = 1;
			else if (set_texture(new, args[i] + 2))
				return (1);
		}
		if (!ft_strncmp(args[i], "n:", 2) && set_normal_map(new, args[i] + 2))
			return (1);
		if (!ft_strncmp(args[i], "r:", 2) && set_reflect(new, args[i] + 2))
			return (1);
		i++;
	}
	return (0);
}
