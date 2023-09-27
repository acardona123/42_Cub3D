/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:30:20 by acardona          #+#    #+#             */
/*   Updated: 2023/09/26 21:35:45 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	ssize_t	len1;
	ssize_t	len2;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-*s2);
	if (!s2)
		return (*s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 < len2)
		return (ft_strncmp(s1, s2, len1 + 1));
	return (ft_strncmp(s1, s2, len2));
}
