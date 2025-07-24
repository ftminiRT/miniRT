/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:45:13 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strdup()  function  returns  a pointer to a new string which is a
duplicate of the string s.  Memory for the new string is obtained with
malloc(3), and can be freed with free(3). */

#include "./includes/libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	i = 0;
	str = 0;
	str = ft_calloc(ft_strlen((const char *)src) + 1, 1);
	if (!(str))
		return (0);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}
/*
#include<stdio.h>
#include<string.h>

int	main(void)
{
	char	str[] = " sasdfasdf ";
	
	printf("%s\n%s", ft_strdup(str), strdup(str));
		
}
*/