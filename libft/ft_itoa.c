/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:55:26 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Alloue (avec malloc(3)) et retourne une chaîne
de caractères représentant l’entier ’n’ reçu en
argument. Les nombres négatifs doivent être gérés. */

#include "./includes/libft.h"

static int	itoa_len(long n)
{
	int	l;

	if (n <= 0)
	{
		l = 1;
		n *= -1;
	}
	else
		l = 0;
	while (n > 0)
	{
		n /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*a;
	long	nb;

	nb = n;
	l = itoa_len(nb);
	a = ft_calloc(l + 1, 1);
	if (!(a))
		return (0);
	if (nb < 0)
	{
		a[0] = '-';
		nb *= -1;
	}
	else if (nb == 0)
		a[0] = '0';
	a[l] = '\0';
	while ((a[0] != '-' && l > 0) || (l > 1))
	{
		l--;
		a[l] = (nb % 10) + '0';
		nb /= 10;
	}
	return (a);
}

/* int	main(void)
{
	int i = 0;
	char *a = ft_itoa(i);
	printf("%s", a);
	free(a);	
} */