/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   any_to_a_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:41:54 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:42 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*calculates the len of the number to be converted into ascii in the
given base*/
int	atoa_len(unsigned long n, int base)
{
	int	l;

	l = 0;
	while (n > 0)
	{
		n /= base;
		l++;
	}
	return (l);
}

/*allocates and initialise the string to be used in ultoa, adds 2 to the len
for the 0x prefix before the pointer*/
char	*ultoa_init(char *a, uintptr_t *nb, int *l, int base)
{
	*l = atoa_len(*nb, base);
	a = ft_calloc(*l + 3, 1);
	if (!(a))
		return (0);
	if (*nb == 0)
		a[0] = '0';
	return (a);
}

/*allocates and initialise the string be used in any_to_ascii function*/
char	*atoa_init(char *a, unsigned long *nb, int *l, int base)
{
	*l = atoa_len(*nb, base);
	a = ft_calloc(*l + 1, 1);
	if (!(a))
		return (0);
	if (*nb < 0)
	{
		a[0] = '-';
		*nb *= -1;
	}
	else if (*nb == 0)
		a[0] = '0';
	return (a);
}

char	*nbzero(char *a)
{
	a = ft_strdup("0");
	if (!(a))
		return (0);
	return (a);
}
