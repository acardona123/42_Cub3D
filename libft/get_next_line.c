/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:46:46 by acardona          #+#    #+#             */
/*   Updated: 2023/01/12 18:47:18 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	b;
	char			*rtn;
	char			*tmp;

	if (fd < 0 || !ft_buffinit(fd, &b, &rtn))
		return (0);
	while (rtn && b.e > 0 && ft_indexn(b.buf + b.s, b.e - b.s) == b.e - b.s)
	{
		tmp = ft_join(rtn, b.buf, b.s, b.e - b.s);
		free(rtn);
		rtn = tmp;
		b.e = read(fd, b.buf, BUFFER_SIZE);
		if (b.e == -1 || !rtn)
			return (0);
		b.s = 0;
	}
	if (rtn && b.e > 0)
	{
		tmp = ft_join(rtn, b.buf, b.s, ft_indexn(b.buf + b.s, b.e - b.s) + 1);
		free(rtn);
		rtn = tmp;
		b.s += ft_indexn(b.buf + b.s, b.e - b.s) + 1;
	}
	return (rtn);
}
