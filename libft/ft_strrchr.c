/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:59:04 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strrchr() function returns a pointer to the last occurrence of the
character c in the string s. */

#include "./includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == c % 256)
		{
			s = s + i;
			return ((char *)s);
		}
		i--;
	}
	return (0);
}

/* #include<stdio.h>
#include<string.h>
int	main()
{
	char s[] = "tripouille";
	printf("%s\n%s", ft_strrchr(s, 't'), strrchr(s, 't'));
} */
