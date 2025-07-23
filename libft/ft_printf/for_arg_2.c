/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_arg_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:48:18 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:49 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*convert the unsigned int given as argument into a string on hexa base and
returns it*/
char	*x_printf(va_list args, t_len *len, int uppcase)
{
	char	*ptr;
	int		nb;

	ptr = 0;
	nb = va_arg(args, int);
	ptr = ft_utoa_hex(nb, uppcase);
	if (!(ptr))
		return (0);
	len->str_l += 2;
	len->temp_l = ft_strlen(ptr);
	return (ptr);
}
