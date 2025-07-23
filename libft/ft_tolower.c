/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:29:27 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* If c is an uppercase letter, tolower() returns its lowercase equivalent, if a
lowercase representation exists in the current locale.  Otherwise, it returns
c.  The tolower_l() function performs the same task, but uses the locale
referred to by the locale handle locale. */

#include "./includes/libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
#include<ctype.h>
#include<stdio.h>
int main()
{
    int test = 'c';
    printf("%c\n%c", (char)ft_tolower(test), (char)tolower(test));
    return(0);
}*/