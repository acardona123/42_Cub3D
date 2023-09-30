/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_tools.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:34:15 by acardona          #+#    #+#             */
/*   Updated: 2023/09/29 18:42:06 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

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
		return (to_error_msg("Wrong texture directory"), FAIL);
	elem = readdir(dir);
	while (elem)
	{
		if (elem->d_type == DT_REG && ft_strlen(elem->d_name) >= 4
			&& !ft_strcmp(elem->d_name + ft_strlen(elem->d_name) - 4, ".xpm"))
			++*cpt;
		elem = readdir(dir);
	}
	closedir(dir);
	if (!*cpt)
		return (to_error_msg("No .xpm file in the texture folder"), FAIL);
	return (SUCCESS);
}

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
