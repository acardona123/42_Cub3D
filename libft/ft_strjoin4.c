/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:25:25 by rbitca            #+#    #+#             */
/*   Updated: 2023/11/19 03:11:24 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin4(const char *s1, const char *s2, const char *s3,
	const char *s4)
{
	int		curpos;
	int		i;
	char	*full;

	if (s1 == NULL || s2 == NULL || s3 == NULL || s4 == NULL)
		return (NULL);
	full = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)
			+ ft_strlen(s4) + 1, sizeof(char));
	if (!full)
		return (NULL);
	curpos = 0;
	i = 0;
	while (s1[i])
		full[curpos++] = s1[i++];
	i = 0;
	while (s2[i])
		full[curpos++] = s2[i++];
	i = 0;
	while (s3[i])
		full[curpos++] = s3[i++];
	i = 0;
	while (s4[i])
		full[curpos++] = s4[i++];
	return (full);
}
