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
	if (!str_is_double(arg))
		return (1);
	new->shine = ft_atod(arg);
	return (0);
}
