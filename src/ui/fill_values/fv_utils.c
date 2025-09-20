/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-20 16:14:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-20 16:14:38 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*dota(t_env *rt, double n)
{
	char	*buf;

	buf = malloc(64);
	if (!buf)
	{
		mega_clean(rt);
		exit(1);
	}
	snprintf(buf, 64, "%.2f", n);
	return (buf);
}
