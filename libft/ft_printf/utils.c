/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:03:23 by tcoeffet          #+#    #+#             */
/*   Updated: 2024/12/13 15:16:44 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strldup(const char *src, int l)
{
	char	*str;
	int		i;

	i = 0;
	str = 0;
	str = ft_calloc(l + 1, 1);
	if (str == 0)
		return (NULL);
	while (l > i && (src[i]))
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}

char	*ft_strljoin(char *s1, char *s2, t_len *len)
{
	char	*str;
	int		i;
	int		l1;
	int		l2;

	l1 = len->toprint_l;
	l2 = len->temp_l;
	i = 0;
	str = 0;
	str = ft_calloc(l1 + l2 + 1, 1);
	if (!(str))
		return (0);
	while (i < l1)
	{
		str[i] = *(char *)s1++;
		i++;
	}
	while (i < l1 + l2)
	{
		str[i] = *(char *)s2++;
		i++;
	}
	return (str);
}
