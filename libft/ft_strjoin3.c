/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:25:25 by rbitca            #+#    #+#             */
/*   Updated: 2023/09/28 22:03:36 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	int		fullsize;
	int		curpos;
	int		i;
	char	*full;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	fullsize = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	full = ft_calloc(fullsize, sizeof(char));
	if (!full)
		return (NULL);
	i = 0;
	curpos = 0;
	while (s1[i])
		full[curpos++] = s1[i++];
	i = 0;
	while (s2[i])
		full[curpos++] = s2[i++];
	i = 0;
	while (s3[i])
		full[curpos++] = s3[i++];
	return (full);
}
