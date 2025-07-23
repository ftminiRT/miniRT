/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   any_to_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:52:53 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 14:18:35 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*convert an unsigned int into an ascii string*/
char	*ft_utoa(unsigned int n)
{
	int				l;
	char			*a;
	unsigned long	nb;

	nb = n;
	a = 0;
	if (n == 0)
		return (nbzero(a));
	a = atoa_init(a, &nb, &l, 10);
	if (!(a))
		return (0);
	while ((a[0] != '-' && l > 0) || (l > 1))
	{
		l--;
		a[l] = (nb % 10) + '0';
		nb /= 10;
	}
	return (a);
}

/*convert a long long int into an ascii string on hexa base*/
char	*ft_ultoa(uintptr_t n)
{
	static char		hexa_low[17] = "0123456789abcdef";
	int				l;
	char			*a;
	uintptr_t		nb;

	nb = n;
	a = 0;
	if (n == 0)
		return (nbzero(a));
	a = ultoa_init(a, &nb, &l, 16);
	if (!(a))
		return (0);
	l += 2;
	while ((l > 2))
	{
		l--;
		a[l] = hexa_low[nb % 16];
		nb /= 16;
	}
	a[0] = '0';
	a[1] = 'x';
	return (a);
}

/*converts an unsigned int into an ascii string on hexa base
the uppcase parameter is a given boolean telling if the letters
should be in (1)upper or (0)lower case*/
char	*ft_utoa_hex(unsigned int n, int uppcase)
{
	int				l;
	char			*a;
	unsigned long	nb;
	static char		hexa_low[17] = "0123456789abcdef";
	static char		hexa_upp[17] = "0123456789ABCDEF";

	nb = n;
	a = 0;
	if (n == 0)
		return (nbzero(a));
	a = atoa_init(a, &nb, &l, 16);
	if (!(a))
		return (0);
	while ((a[0] != '-' && l > 0) || (l > 1))
	{
		l--;
		if (uppcase)
			a[l] = hexa_upp[nb % 16];
		else
			a[l] = hexa_low[nb % 16];
		nb /= 16;
	}
	return (a);
}
