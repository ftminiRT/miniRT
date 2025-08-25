/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:40:36 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/24 12:40:39 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_line(char *line, int line_count, int *is_empty)
{
	char	**split;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (perror("miniRT :"), 1);
	if (!split[0])
		is_empty = is_empty + 1;
	else if (check_first_arg(split[0]))
		ret = 1;
	else if (check_next_args(split, split[0]))
		ret = 1;
	ft_free_split(split);
	return (ret);
}

int	check_file(char *file)
{
	int		fd;
	int		line_count;
	int		is_empty;
	char	*line;

	is_empty = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("miniRT :"), 1);
	line = get_next_line(fd);
	if (!line)
		return (1);
	line_count = 0;
	while (line)
	{
		if (check_line(line, line_count, &is_empty))
			return (free(line), close(fd), 1);
		free(line);
		line = (get_next_line(fd));
		line_count++;
	}
	if (is_empty == line_count)
		return (free(line), close(fd), \
			write(STDERR_FILENO, "miniRT : file error\n", 21), 1);
	return (free(line), close(fd), 0);
}
