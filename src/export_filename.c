/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 15:43:03 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 15:43:03 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*build_export_path(int i, t_env *rt)
{
	char	*num_str;
	char	*temp;
	char	*filename;

	num_str = ft_itoa(i);
	if (!num_str && mega_clean(rt))
		exit(1);
	temp = ft_strjoin("export", num_str);
	free(num_str);
	if (!temp && mega_clean(rt))
		exit(1);
	filename = ft_strjoin(temp, ".rt");
	free(temp);
	if (!filename && mega_clean(rt))
		exit(1);
	temp = ft_strjoin("assets/exports/", filename);
	free(filename);
	return (temp);
}

char	*get_next_export_filename(t_env *rt)
{
	char	*filename;
	int		i;

	i = 0;
	while (++i <= 9999)
	{
		filename = build_export_path(i, rt);
		if (!filename)
			return (NULL);
		if (access(filename, F_OK) == -1)
			return (filename);
		free(filename);
	}
	return (NULL);
}
