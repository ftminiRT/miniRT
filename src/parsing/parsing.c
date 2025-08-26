/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:14:21 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 19:20:24 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_line_data(char *line, t_env *rt)
{
	char	**split;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (perror("miniRT :"), 1);
	else if (!ft_strncmp(split[0], "A", 2))
		ret = init_amblight(split, rt);
	else if (!ft_strncmp(split[0], "C", 2))
		ret = init_cam(split, rt);
	else if (!ft_strncmp(split[0], "L", 2))
		ret = init_spotlight(split, rt);
	else if (!ft_strncmp(split[0], "sp", 3))
		ret = init_sphere(split, rt);
	else if (!ft_strncmp(split[0], "pl", 3))
		ret = init_plane(split, rt);
	else if (!ft_strncmp(split[0], "cy", 3))
		ret = init_cylinder(split, rt);
	else
		ret = 1;
	ft_free_split(split);
	if (ret)
		return (write (2, "miniRT : file content error\n", 29), 1);
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
		write(2, "Error : file extension invalid\n", 32);
		return (1);
	}
	return (0);
}

int	parsing(t_env *rt, char *file)
{
	int		fd;
	char	*line;

	rt->objects = NULL;
	if (check_file(file))
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("miniRT ");
		return (1);
	}
	line = get_next_line(fd);
	if (!line)
		return (1);
	while (line)
	{
		if (init_line_data(line, rt))
			return (free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (!(rt->cam.is_set && rt->ambient.is_set && rt->spot.is_set));
}
