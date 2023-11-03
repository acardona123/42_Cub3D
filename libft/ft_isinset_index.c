/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinset_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:08:43 by acardona          #+#    #+#             */
/*   Updated: 2023/11/02 16:37:40 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief checks if a charis in a string.If so return the index in the string,
 *		otherwise returns -1
 * 
 * @param c char to check
 * @param set string to look in
 * @return int 
 */
int	ft_isinset_index(char c, char *set)
{
	int	i;

	if (!set)
		return (-1);
	i = -1;
	while (++i)
		if (c == set[i])
			return (i);
	return (-1);
}
