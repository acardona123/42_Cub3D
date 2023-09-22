/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlst_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:11:03 by acardona          #+#    #+#             */
/*   Updated: 2023/05/13 18:11:05 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*return the number of strings in a null terminated char** */
size_t	ft_strlst_len(char **strlst)
{
	size_t	i;

	i = 0;
	while (strlst[i])
		i++;
	return (i);
}
