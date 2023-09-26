/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:07:37 by acardona          #+#    #+#             */
/*   Updated: 2023/09/26 16:11:52 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

void	to_lstfree(t_list **lst)
{
	t_list	*elem;
	t_list	*tmp;

	if (!lst)
		return ;
	elem = *lst;
	while (elem)
	{
		if (elem->content)
			free(elem->content);
		tmp = elem;
		elem = elem->next;
		free(tmp);
	}
}
