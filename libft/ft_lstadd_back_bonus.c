/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:46:02 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Ajoute l’élément ’new’ à la fin de la liste. */

#include "./includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!(*lst))
		return (ft_lstadd_front(lst, new));
	last = ft_lstlast(*lst);
	last->next = new;
}
