/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_arg_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:03:23 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 14:18:42 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*converts the char argument into a string and returns it*/
char	*c_printf(va_list args, t_len *len)
{
	char	*ptr;

	ptr = 0;
	ptr = ft_calloc(2, sizeof(char));
	if (!(ptr))
		return (0);
	ptr[0] = (char)va_arg(args, int);
	len->str_l += 2;
	len->temp_l = 1;
	return (ptr);
}

/*convert the string argument into a string and returns it*/
char	*s_printf(va_list args, t_len *len)
{
	char	*ptr;
	char	*str;

	ptr = 0;
	str = va_arg(args, char *);
	if (!(str))
		ptr = ft_strdup("(null)");
	else
		ptr = ft_strdup(str);
	if (!(ptr))
		return (0);
	len->str_l += 2;
	len->temp_l = ft_strlen(ptr);
	return (ptr);
}

/*convert the pointer argument into a string and returns it*/
char	*p_printf(va_list args, t_len *len)
{
	char		*ptr;
	uintptr_t	nb;

	ptr = 0;
	nb = va_arg(args, uintptr_t);
	if (nb == 0)
		ptr = ft_strdup("(nil)");
	else
		ptr = ft_ultoa(nb);
	if (!(ptr))
		return (0);
	len->str_l += 2;
	len->temp_l = ft_strlen(ptr);
	return (ptr);
}

/*convert the integer argument into a string and returns it*/
char	*d_printf(va_list args, t_len *len)
{
	char	*ptr;
	int		nb;

	ptr = 0;
	nb = va_arg(args, int);
	ptr = ft_itoa(nb);
	if (!(ptr))
		return (0);
	len->str_l += 2;
	len->temp_l = ft_strlen(ptr);
	return (ptr);
}

/*convert the unsigned int into a string and returns it*/
char	*u_printf(va_list args, t_len *len)
{
	char	*ptr;
	int		nb;

	ptr = 0;
	nb = va_arg(args, unsigned int);
	ptr = ft_utoa(nb);
	if (!(ptr))
		return (0);
	len->str_l += 2;
	len->temp_l = ft_strlen(ptr);
	return (ptr);
}
