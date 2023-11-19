/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:34:15 by acardona          #+#    #+#             */
/*   Updated: 2023/11/19 00:40:17 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

/**
 * @brief checks if an element of a directory is a .xpm regular file
 * 
 * @param elem 
 * @return true if it is
 * @return false else
 */
bool	in_2_tools_is_xpm_file(struct dirent *elem)
{
	if (elem->d_type == DT_REG && ft_strlen(elem->d_name) >= 4
		&& !ft_strcmp(elem->d_name + ft_strlen(elem->d_name) - 4, ".xpm"))
		return (true);
	return (false);
}

#ifdef BONUS

/**
 * @brief counts the number of .xpm files in a repertory
 * 
 * @param dir_name 
 * @param cpt 
 * @return true SUCCESS, updates cpt
 * @return FAIL FAILURE if can't open the directory
 */
t_bool	in_2_tools_count_xpm_files_in_folder(char *dir_name,
	unsigned int *cpt)
{
	DIR				*dir;
	struct dirent	*elem;

	*cpt = 0;
	dir = opendir(dir_name);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	elem = readdir(dir);
	while (elem)
	{
		if (in_2_tools_is_xpm_file(elem))
			++*cpt;
		elem = readdir(dir);
	}
	closedir(dir);
	if (!*cpt)
		return (to_error_msg(MSG_NO_XPM_IN_FOLDER), FAIL);
	return (SUCCESS);
}

#endif

/**
 * @brief sorts the frames table of the animated texture by ascii order
 * 
 * @param frame_array table of the t_animated_texture to sort
 * @param frame_number number of frames to sort 
 */
void	in_2_tools_sort_anim_text_table(t_static_texture *frame_array,
	unsigned int frame_number)
{
	t_static_texture	tmp;
	unsigned int		i;
	unsigned int		j;

	i = 0;
	while (++i < frame_number)
	{
		j = i;
		while (j > 0
			&& ft_strcmp(frame_array[j].path, frame_array[j - 1].path) <= 0)
		{
				tmp = frame_array[j - 1];
				frame_array[j - 1] = frame_array[j];
				frame_array[j] = tmp;
			--j;
		}
	}
}
