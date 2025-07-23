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
	if (split[0][0] == 'A')
		ret = init_amblight(split, rt);
	if (split[0][0] == 'C')
		ret = init_cam(split, rt);
	if (split[0][0] == 'L')
		ret = init_spotlight(split, rt);
	if (split[0][0] == 's')
		ret = init_sphere(split, rt);
	if (split[0][0] == 'p')
		ret = init_plane(split, rt);
	if (split[0][0] == 'c')
		ret = init_cylinder(split, rt);
	ft_free_split(split);
	if (ret)
		return (perror("miniRT :"), 1);
	return (0);
}

int	check_file(char *file)
{
	(void) file;
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
		return (1);
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
	return (0);
}
