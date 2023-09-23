/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:07:08 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 18:40:17 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	if (!s)
	{
		write(2, "Error:\nft_memset with NULL pointer\n", 35);
		return (NULL);
	}
	i = 0;
	if (s)
	{
		while (i < n)
		{
			((char *)s)[i] = (char)c;
			i++;
		}
	}
	return ((void *)s);
}
