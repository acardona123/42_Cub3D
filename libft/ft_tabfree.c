/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:28:15 by acardona          #+#    #+#             */
/*   Updated: 2023/09/26 21:10:31 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabfree(char **tab)
{
	ssize_t	len;

	if (!tab)
		return ;
	len = ft_tablen(tab);
	while (len >= 0)
		free(tab[len--]);
	free(tab);
	return ;
}
