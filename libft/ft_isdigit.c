/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:31:58 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* checks for a digit (0 through 9). */

#include "./includes/libft.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
int	main(int argc, char **argv)
{
	(void) argc;
	printf("%d\n%d", isdigit(atoi(argv[1])), ft_isdigit(atoi(argv[1])));
}
*/