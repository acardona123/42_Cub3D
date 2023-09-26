/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:15:59 by acardona          #+#    #+#             */
/*   Updated: 2023/09/26 15:25:39 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	t_list	*elem;

	elem = lst;
	while (elem)
	{
		ft_putstr_fd(elem->content, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		elem = elem->next;
	}
}
