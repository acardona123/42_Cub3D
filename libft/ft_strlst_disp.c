/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlst_disp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 01:55:06 by alexcardona       #+#    #+#             */
/*   Updated: 2023/06/18 15:34:44 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strlst_disp(char **lst)
{
	size_t	i;
	char	nb[11];

	if (!lst)
		return ;
	i = 0;
	while (lst[i])
	{
		ft_itoa_simple(nb, ft_strlen(lst[i]));
		write(1, nb, ft_strlen(nb));
		write(1, ": {", 3);
		write (1, lst[i], ft_strlen(lst[i]));
		write(1, "}\n", 2);
		i++;
	}
	write(1, "(null)\n", 7);
}
