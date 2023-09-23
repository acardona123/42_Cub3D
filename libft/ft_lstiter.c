/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:54:26 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 18:43:28 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*pelem;

	if (!lst || !f)
		return ;
	pelem = lst;
	while (pelem)
	{
		(*f)(pelem->content);
		pelem = pelem->next;
	}
}
