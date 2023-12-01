/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:16:56 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 20:47:52 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

static size_t	_to_file_build_path_len(char *name0, char *name1, char *name2,
					char *name3);

/**
 * @brief returns the path formed by the succession of direcoties/file names
 *		(ex: name0/name1/name2/name3)
 *		or subparts of it if some arguments are null (ex: name0/name1))
 * 
 * @param name0 
 * @param name1 
 * @param name2 
 * @param name3 
 * @return char* 	success : the complete path (no arg free)
 *					fail: NULL (no arg  free), err msg displayed
 */
char	*to_file_build_path(char *name0, char *name1, char *name2, char *name3)
{
	char	*rtn;
	size_t	len;
	char	**names;
	size_t	i;

	len = _to_file_build_path_len(name0, name1, name2, name3);
	if (!len)
		return (NULL);
	rtn = ft_calloc(len + 1, sizeof(char));
	if (!rtn)
		return (to_error_msg(MSG_BAD_ALLOC), NULL);
	names = (char *[5]){name0, name1, name2, name3, NULL};
	i = 0;
	while (*names)
	{
		len = ft_strlen(*names);
		ft_memcpy(rtn + i, *names, len);
		if (!*(++names) || !**names)
			return (rtn);
		i += len;
		rtn[i++] = '/';
	}
	return (rtn);
}

/**
 * @brief subfunction of to_file_build_path: gives the length of the complete
 *		path
 * 
 * @param name0 
 * @param name1 
 * @param name2 
 * @param name3 
 * @return size_t the length of the path
 */
static size_t	_to_file_build_path_len(char *name0, char *name1, char *name2,
	char *name3)
{
	size_t	len_tot;

	len_tot = 0;
	if (!name0 || !*name0)
		return (0);
	len_tot += ft_strlen(name0);
	if (!name1 || !*name1)
		return (len_tot);
	len_tot += 1 + ft_strlen(name1);
	if (!name2 || !*name2)
		return (len_tot);
	len_tot += 1 + ft_strlen(name2);
	if (!name3 || !*name3)
		return (len_tot);
	len_tot += 1 + ft_strlen(name3);
	return (len_tot);
}

/*
int	main(int ac, char **av)
{
	static char	*names[4] = {NULL, NULL, NULL, NULL};
	char		*path;
	int			i;

	i = -1;
	while (++i < ac - 1 && i < 4)
		names[i] = av[1 + i];
	printf("{%s}, {%s}, {%s}, {%s}\n", names[0], names[1], names[2], names[3]);
	path = to_file_build_path(names[0], names[1], names[2], names[3]);
	printf("path: {%s}\n", path);
	if (path)
		free(path);
	return (0);
}
*/