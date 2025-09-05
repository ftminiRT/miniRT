/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:14:21 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/04 23:09:57 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_obj_bonus(char **split, t_env *rt)
{
	if (!ft_strncmp(split[0], "co", 3))
		return (init_cone(split, rt));
	else if (!ft_strncmp(split[0], "to", 3))
		return (init_tore(split, rt));
	else if (!ft_strncmp(split[0], "ri", 3))
		return (init_ring(split, rt));
	else if (!ft_strncmp(split[0], "tr", 3))
		return (init_triangle(split, rt));
	else if (!ft_strncmp(split[0], "pa", 3))
		return (init_boloid(split, rt, OT_PARA));
	else if (!ft_strncmp(split[0], "hy", 3))
		return (init_boloid(split, rt, OT_HYP));
	else if (!ft_strncmp(split[0], "mo", 3))
		return (init_moebius(split, rt));
	else
		return (1);
}

int	init_obj(char **split, t_env *rt)
{
	if (!ft_strncmp(split[0], "A", 2))
		return (init_amblight(split, rt));
	else if (!ft_strncmp(split[0], "C", 2))
		return (init_cam(split, rt));
	else if (!ft_strncmp(split[0], "L", 2))
		return (init_spotlight(split, rt));
	else if (!ft_strncmp(split[0], "sp", 3))
		return (init_sphere(split, rt));
	else if (!ft_strncmp(split[0], "pl", 3))
		return (init_plane(split, rt));
	else if (!ft_strncmp(split[0], "cy", 3))
		return (init_cylinder(split, rt));
	else
		return (init_obj_bonus(split, rt));
}

int	init_line_data(char *line, t_env *rt, int i)
{
	char	**split;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (perror("miniRT :"), 1);
	else
		ret = init_obj(split, rt);
	ft_free_split(split);
	if (ret)
	{
		ret = write (2, "miniRT : file content error at line ", 37);
		ret = write (2, ft_itoa(i + 1), ft_strlen(ft_itoa(i + 1)));
		ret = write (2, "\n", 1);
		return (1);
	}
	return (0);
}

int	check_file(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (ft_strncmp(file + i - 3, ".rt", 4))
	{
		i = write(2, "Error : file extension invalid\n", 32);
		return (1);
	}
	return (0);
}

int	parsing(t_env *rt, char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	rt->objects = NULL;
	if (check_file(file))
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("miniRT "), 1);
	line = get_next_line(fd);
	if (!line)
		return (1);
	while (line)
	{
		if (init_line_data(line, rt, i))
			return (free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (!(rt->cam.is_set && rt->ambient.is_set && rt->spot.is_set));
}
