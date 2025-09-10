#include "minirt.h"

static int	setup_export_file(char *filename, t_env *rt)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit_from_export((t_vec3int){0, 0, 0}, rt, filename,
			"Erreur lors de la création du fichier");
	return (fd);
}

static int	backup_stdout(int fd, char *filename, t_env *rt)
{
	int	stdout_backup;

	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
		exit_from_export((t_vec3int){1, fd, 0}, rt, filename,
			"Erreur lors de la sauvegarde de stdout");
	return (stdout_backup);
}

static void	redirect_to_file(int fd, int stdout_backup, char *filename,
		t_env *rt)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_from_export((t_vec3int){2, fd, stdout_backup}, rt, filename,
			"Erreur lors de la redirection");
}

static int	ensure_export_dir_exists(void)
{
	struct stat st;

	if (stat("exports", &st) == -1)
	{
		if (mkdir("exports", 0755) == -1)
		{
			fprintf(stderr, "Erreur lors de la création du dossier exports: %s\n",
				strerror(errno));
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
		printf("Erreur: impossible de générer un nom de fichier\n");
		fflush(stdout);
		return ;
	}
	fd = setup_export_file(filename, rt);
	stdout_backup = backup_stdout(fd, filename, rt);
	redirect_to_file(fd, stdout_backup, filename, rt);
	debug_print_set(rt);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		perror("Erreur lors de la restauration de stdout");
	close(stdout_backup);
	close(fd);
	printf("Scène exportée vers: %s\n", filename);
	free(filename);
}
