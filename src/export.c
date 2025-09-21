/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:40:12 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:40:12 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	setup_export_file(char *filename, t_env *rt)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit_from_export((t_vec3int){0, 0, 0}, rt, filename,
			"Error :\ncan't generate file");
	return (fd);
}

static int	backup_stdout(int fd, char *filename, t_env *rt)
{
	int	stdout_backup;

	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
		exit_from_export((t_vec3int){1, fd, 0}, rt, filename,
			"Error :\ncan't backup stdout");
	return (stdout_backup);
}

static void	redirect_to_file(int fd, int stdout_backup, char *filename,
		t_env *rt)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_from_export((t_vec3int){2, fd, stdout_backup}, rt, filename,
			"Error :\nredirection failed");
}

static int	ensure_export_dir_exists(void)
{
	struct stat	st;

	if (stat("assets/exports", &st) == -1)
	{
		if (mkdir("assets/exports", 0755) == -1)
		{
			ft_putstr_fd("Error :\nissue while creating export file: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
	}
	return (0);
}

void	export_to_rt(t_env *rt)
{
	char	*filename;
	int		fd;
	int		stdout_backup;

	if (ensure_export_dir_exists())
		return ;
	filename = get_next_export_filename(rt);
	if (!filename)
	{
		ft_putendl_fd("Error :\ncan't generate file name", 2);
		fflush(stdout);
		return ;
	}
	fd = setup_export_file(filename, rt);
	stdout_backup = backup_stdout(fd, filename, rt);
	redirect_to_file(fd, stdout_backup, filename, rt);
	print_set(rt);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		perror("Error :\n");
	close(stdout_backup);
	close(fd);
	printf("Success ! Set exported to : %s\n", filename);
	free(filename);
}
