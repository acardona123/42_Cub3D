/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:21:28 by acardona          #+#    #+#             */
/*   Updated: 2022/11/24 11:38:52 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Return the index of the first \n of a max memory spaces and return
 max if no \n is found*/
ssize_t	ft_indexn(char *str, ssize_t max)
{
	ssize_t	i;

	i = 0;
	if (!str)
		return (max);
	while (i < max)
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

/*Join s1 and s2_len elements of s2 + s2_start in a unique string (malloc) and
 free s1 BUT NOT s2 (because when used the function  will take the buffer as a
 second argument)*/
char	*ft_join(char *s1, char *s2, size_t s2_start, size_t len)
{
	char	*rtn;
	size_t	len_s1;
	size_t	i;
	size_t	j;

	len_s1 = 0;
	while (s1[len_s1])
		len_s1++;
	rtn = malloc((len_s1 + len + 1));
	if (!rtn)
		return (0);
	rtn[len_s1 + len] = 0;
	i = -1;
	while (++i < len_s1)
		rtn[i] = s1[i];
	j = -1;
	while (++j < len)
		rtn[i + j] = *(s2 + s2_start + j);
	return (rtn);
}

/*Initialidation of the buffer element if needed and initialisation of the
 return char*/
char	*ft_buffinit(int fd, t_buffer *b, char **rtn )
{
	if (b->e == 0 || b->e == b->s)
	{
		b->e = read(fd, b->buf, BUFFER_SIZE);
		b->s = 0;
	}
	if (b->e < 1)
		return (0);
	*rtn = malloc(sizeof(char));
	if (!rtn)
		return (0);
	**rtn = 0;
	return (*rtn);
}
