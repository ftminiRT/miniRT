/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:35:20 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The calloc() function allocates memory for an array of nmemb elements of size
bytes each and returns a pointer to the allocated memory.  The memory is set
to zero. */

#include "./includes/libft.h"

/* void	ft_bzero(void *s, size_t n); */

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	ptr = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((size * nmemb > 2147483647) || (SIZE_MAX / size <= nmemb))
		return (0);
	ptr = malloc(sizeof(char) * (size * nmemb));
	if (!(ptr))
		return (0);
	ft_bzero(ptr, nmemb * size);
	return ((void *)ptr);
}

/* void	ft_bzero(void *s, size_t n)
{
	while (s && (n-- > 0))
		*(char *)s++ = 0;
} */