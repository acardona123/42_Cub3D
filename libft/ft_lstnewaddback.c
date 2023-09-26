/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewaddback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:47:02 by acardona          #+#    #+#             */
/*   Updated: 2023/09/26 14:50:15 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstnewaddback(t_list **lst, char *content)
{
	t_list	*elem;

	if (!lst || !content)
		return (1);
	elem = ft_lstnew(content);
	if (!elem)
		return (1);
	ft_lstadd_back(lst, elem);
	return (0);
}
