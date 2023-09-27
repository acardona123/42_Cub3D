/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:30:35 by acardona          #+#    #+#             */
/*   Updated: 2023/09/26 19:32:39 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_tablen(char **tab)
{
	ssize_t	len;

	if (!tab)
		return (0);
	len = 0;
	while (tab[len])
		++len;
	return (len);
}
