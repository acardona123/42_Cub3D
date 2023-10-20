/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1_mapformat_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:14:57 by acardona          #+#    #+#             */
/*   Updated: 2023/10/20 15:22:40 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

/**
 * @brief tries to open the file which name is given in arguments
 * 
 * @param file_name 
 * @return int 	error: -1 (err msg displayed)
 *				success: fd of the open file
 */
int	in_1_file_opening(char *file_name)
{
	int	fd_input;

	if (ft_strlen(file_name) < 4
		|| ft_strncmp(".cub", file_name + ft_strlen(file_name) - 4, 4))
	{
		to_error_msg(MSG_MAP_FILE_FORMAT);
		return (-1);
	}
	fd_input = open(file_name, O_RDWR);
	if (fd_input == -1)
		to_error_msg(MSG_MAP_OPEN_FAIL);
	return (fd_input);
}

#ifdef BONUS

/**
 * @brief checks if a line is describing a prameter of the map (or is empty)
 * 
 * @param line 
 * @return true param line
 * @return false 
 */
bool	in_1_line_is_parameter(char *line)
{
	while (ft_iswhitespace(*line))
		++line;
	if (!*line || !ft_strncmp("SO ", line, 3) || !ft_strncmp("NO ", line, 3)
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3)
		|| !ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2)
		|| !ft_strncmp("DF ", line, 3) || !ft_strncmp("DS ", line, 3))
		return (true);
	return (false);
}

#else

/**
 * @brief checks if a line is describing a prameter of the map (or is empty)
 * 
 * @param line 
 * @return true param line
 * @return false (nothing displayed)
 */
bool	in_1_line_is_parameter(char *line)
{
	while (ft_iswhitespace(*line))
		++line;
	if (!*line || !ft_strncmp("SO ", line, 3) || !ft_strncmp("NO ", line, 3)
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3)
		|| !ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2))
		return (true);
	return (false);
}

#endif

/**
 * @brief checks if a line is empty (only whitespaces)
 * 
 * @param line 
 * @return true is empty
 * @return false (nothing dislayed)
 */
bool	in_1_line_is_empty(char *line)
{
	while (ft_iswhitespace(*line))
		++line;
	if (*line)
		return (false);
	return (true);
}
