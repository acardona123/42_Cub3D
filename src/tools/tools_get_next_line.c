/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:47:18 by acardona          #+#    #+#             */
/*   Updated: 2023/12/05 19:57:56 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doors.h"

static int		_to_get_next_line_sub(int fd, char *buff, char **line,
					size_t *idx_start);
static size_t	_to_ft_strlen_n(char *str);
static int		_to_ft_strjoin_free(char **dst, char *append);
static int		_to_read(int fd, char *buff, size_t *idx_start);

int	to_get_next_line(int fd, char **dest)
{
	static char		buff[BUFFER_SIZE + 1] = {0};
	static size_t	idx_start = 0;
	size_t			len_n;
	char			*line;

	if (fd < 0 || !dest)
		return (idx_start = 0, 0);
	*dest = NULL;
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (idx_start = 0, to_error_msg(MSG_BAD_ALLOC), 1);
	if (_to_get_next_line_sub(fd, buff, &line, &idx_start) == 1 || !line)
		return (*dest = NULL, (*buff != 0));
	if (!*buff)
		return (idx_start = 0, *dest = line, 0);
	len_n = _to_ft_strlen_n(buff + idx_start);
	if ((buff + idx_start)[len_n])
	{
		(buff + idx_start)[len_n] = 0;
		if (_to_ft_strjoin_free(&line, buff + idx_start))
			return (idx_start = 0, free(line), *dest = NULL, 1);
		idx_start += len_n + 1;
	}
	*dest = line;
	return (0);
}

static int	_to_get_next_line_sub(int fd, char *buff, char **line,
	size_t *idx_start)
{
	size_t			len_n;
	int				read_cpt;

	if (*idx_start == 0 || !buff[*idx_start])
	{
		read_cpt = _to_read(fd, buff, idx_start);
		if (read_cpt == -1)
			return (free(*line), *line = NULL, *buff = 1, 1);
		else if (!read_cpt)
			return (free(*line), *line = NULL, *buff = 0, 0);
	}
	len_n = _to_ft_strlen_n(buff + *idx_start);
	while (*buff && !(buff + *idx_start)[len_n])
	{
		if (_to_ft_strjoin_free(line, buff + *idx_start))
			return (free(*line), *line = NULL, *idx_start = 0, 1);
		if (_to_read(fd, buff, idx_start) == -1)
			return (1);
		len_n = _to_ft_strlen_n(buff);
	}
	return (0);
}

static size_t	_to_ft_strlen_n(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		++i;
	return (i);
}

static int	_to_ft_strjoin_free(char **dst, char *append)
{
	char	*new_str;
	ssize_t	i;
	ssize_t	j;

	new_str = ft_calloc(ft_strlen(*dst) + ft_strlen(append) + 1,
			sizeof(char));
	if (!new_str)
		return (to_error_msg(MSG_BAD_ALLOC), 1);
	i = -1;
	while (*dst && (*dst)[++i])
		new_str[i] = (*dst)[i];
	j = -1;
	while (append && append[++j])
		new_str[i + j] = append[j];
	free(*dst);
	*dst = new_str;
	return (0);
}

static int	_to_read(int fd, char *buff, size_t *idx_start)
{
	int				read_size;

	*idx_start = 0;
	read_size = read(fd, buff, BUFFER_SIZE);
	if (read_size < 0)
		return (to_error_msg(MSG_BAD_READ), read_size);
	buff[read_size] = 0;
	return (read_size);
}
