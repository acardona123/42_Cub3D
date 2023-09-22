/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlst_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:36:03 by alexcardona       #+#    #+#             */
/*   Updated: 2023/04/13 01:32:25 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strlst_free(char **lst)
{
	int	i;

	if (!lst)
		return (NULL);
	i = -1;
	while (lst[++i] != NULL)
		free(lst[i]);
	free(lst);
	return (NULL);
}
