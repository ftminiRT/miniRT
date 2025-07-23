/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:12:20 by tcoeffet          #+#    #+#             */
/*   Updated: 2024/12/13 15:16:39 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
deals with any arg following a '%' char. return adress of a malloc'd string
containing the argument translated to ascii. returns 0 and free on alloc error
*/
char	*add_arg(va_list args, const char *str, t_len *len)
{
	static char	pct[2] = {'%', '\0'};

	if (str[len->str_l + 1] == 'c')
		return (c_printf(args, len));
	else if (str[len->str_l + 1] == 's')
		return (s_printf(args, len));
	else if (str[len->str_l + 1] == 'p')
		return (p_printf(args, len));
	else if (str[len->str_l + 1] == 'd' || str[len->str_l + 1] == 'i')
		return (d_printf(args, len));
	else if (str[len->str_l + 1] == 'u')
		return (u_printf(args, len));
	else if (str[len->str_l + 1] == 'x')
		return (x_printf(args, len, 0));
	else if (str[len->str_l + 1] == 'X')
		return (x_printf(args, len, 1));
	else if (str[len->str_l + 1] == '%')
	{
		len->str_l += 2;
		len->temp_l = 1;
		return (ft_strdup(pct));
	}
	return (0);
}

/* alloc and returns a string containing str[0] to str[i] and replace last 
caracter with char c */
char	*ft_strjoin_char(char const *s1, char c, t_len *len)
{
	size_t		j;
	void		*tofree;
	char		*str;

	if (!(s1))
	{
		str = ft_calloc(2, sizeof(char));
		if (!(str))
			return (0);
		*str = c;
		return (str);
	}
	tofree = (void *)s1;
	j = 0;
	str = ft_calloc(len->toprint_l + 2, sizeof(char));
	if (!(str))
		return (0);
	while (j < len->toprint_l)
	{
		str[j] = *(char *)s1++;
		j++;
	}
	str[j] = c;
	str[j + 1] = '\0';
	return (free(tofree), str);
}

/*translates the argument after the % char and add it to the
main toprint string*/
char	*ft_va_manager(const char *str, va_list args, t_len *len, char *toprint)
{
	char	*temp;
	char	*new;

	new = 0;
	temp = 0;
	temp = add_arg(args, str, len);
	if (!(temp))
	{
		free(temp);
		return (0);
	}
	new = ft_strljoin(toprint, temp, len);
	len->toprint_l += len->temp_l;
	free(temp);
	free(toprint);
	if (!(new))
		return (0);
	return (new);
}

/*checks if the next character in the string str is to be printed or is
an argument to translate and add either to the main string*/
char	*fill_str(const char *str, va_list args, char *toprint, t_len *len)
{
	while (str[len->str_l])
	{
		if (str[len->str_l] == '%')
		{
			toprint = ft_va_manager(str, args, len, toprint);
			if (!(toprint))
			{
				free(toprint);
				return (0);
			}
		}
		if (str[len->str_l] != '%' && str[len->str_l])
		{
			toprint = (ft_strjoin_char(toprint, str[len->str_l], len));
			if (!toprint)
				return (0);
			len->str_l++;
			len->toprint_l++;
		}
	}
	return (toprint);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_len	*len;
	char	*toprint;
	size_t	temp;

	len = malloc(sizeof (t_len));
	if (!(len))
		return (0);
	len->toprint_l = 0;
	len->str_l = 0;
	len->temp_l = 0;
	toprint = 0;
	toprint = malloc(1);
	if (!(toprint))
		return (0);
	toprint[0] = 0;
	va_start(args, str);
	toprint = fill_str(str, args, toprint, len);
	if (!(toprint))
		return (va_end(args), -1);
	temp = len->toprint_l;
	write(1, toprint, temp);
	return (va_end(args), free(toprint), free(len), temp);
}

/* int	main(void)
{
	printf("%p printf \n", -1);
	ft_printf("%p ft_printf \n", -1);
} */

/* int	main(void)
{
	char *str = "str";
	int d = -2147483648, i = 1;
	unsigned int u = 2147483648;
	unsigned int X = 3577654221;
	unsigned int x = 3245678780;
	printf("%cpct %%\nc %c\ns %s\nd %d\ni %i\nu %u\np %p\nX %X\nx %x\n\
	(printf)\n\n\n", '\n', 'c', str, d, i, u, str, X, x);
	ft_printf("%cpct %%\nc %c\ns %s\nd %d\ni %i\nu %u\np %p\nX %X\nx %x\n\
	(ft_printf)", '\n', 'c', str, d, i, u, str, X, x);
} */
