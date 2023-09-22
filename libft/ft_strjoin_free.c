/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexcardona <alexcardona@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:32:24 by alexcardona       #+#    #+#             */
/*   Updated: 2023/06/08 22:33:00 by alexcardona      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s3;
	size_t	ltot;

	ltot = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc((ltot + 1) * sizeof(char));
	if (!s3)
		return (free(s1), free(s2), NULL);
	ft_strlcpy(s3, s1, ft_strlen(s1) + 1);
	ft_strlcpy(s3 + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	free(s1);
	free(s2);
	return (s3);
}
