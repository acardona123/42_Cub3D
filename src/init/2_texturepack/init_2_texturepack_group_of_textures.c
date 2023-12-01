/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_group_of_textures.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:14:50 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:08:23 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static t_bool	_in_2_textu_group_init_from_file(void *mlx,
					t_group_of_textures *textures_group, char **file_name);

#ifdef BONUS

/**
 * @brief imports all the textures of the t_group_of_textures, based on the
 *		given texture_name that referes either to a file (the group will only
 *		contain one texture (without animations) or to a directory that contains
 *		all animations files (for not animated textures)
 *		ou directories (animated))
 * 
 * @param mlx 
 * @param textures_group texture_group destination for the textures
 * @param texture_name pointer to the name of the file/directory, *texture_name
 *			is set to NULL if it referes to a files (the string is directly
 *			used as path in the static texture and need to be extracted to
 *			avoid free in parent function)
 * @return t_bool	SUCCESS if all textures have been imported (at least one),
 *						*texture_name updatded to NULL if it is a *.xpm file. 
 *					FAIL if error during the importation or no texture found,
 *						err msg displayed.
 */
t_bool	in_2_textu_group_init(void *mlx, t_group_of_textures *textures_group,
	char **texture_name)
{
	DIR	*dir;

	if (textures_group->group_len)
		return (to_error_msg(MSG_TEXTURE_MULTIPLE_DEF), FAIL);
	dir = opendir(*texture_name);
	if (dir)
		return (closedir(dir), in_2_textu_group_init_from_dir(mlx,
				textures_group, *texture_name));
	if (errno == ENOENT)
		return (to_error_msg(MSG_TEXTURE_DONT_EXIST), FAIL);
	else if (errno != ENOTDIR)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	return (_in_2_textu_group_init_from_file(mlx, textures_group,
			texture_name));
}

#else

/**
 * @brief imports the texture of the t_group_of_textures, based on the given
 *		texture_name. It must be a.xpm file (the group will only contain
 *		one texture (without animations). Unlike with BONUS directories aren't
 *		allowed as textures containers.
 * 
 * @param mlx 
 * @param textures_group texture_group destination for the textures
 * @param texture_name pointer to the name of the file to import
 * @return t_bool	SUCCESS if the texture have been imported, *texture_name
 *						updated to NULL
 *					FAIL if error during the importation, err msg displayed.
 */
t_bool	in_2_textu_group_init(void *mlx, t_group_of_textures *textures_group,
	char **texture_name)
{
	int	is_dir;

	if (textures_group->group_len)
		return (to_error_msg(MSG_TEXTURE_MULTIPLE_DEF), FAIL);
	is_dir = open(*texture_name, O_RDONLY | O_DIRECTORY);
	if (is_dir >= 0)
		return (close(is_dir), to_error_msg(MSG_OPENDIR_FORBIDDEN), FAIL);
	else if (errno == EACCES)
		return (to_error_msg(MSG_OPENDIR_FORBIDDEN), FAIL);
	return (_in_2_textu_group_init_from_file(mlx, textures_group,
			texture_name));
}

#endif

/**
 * @brief consideres the given name (value) as a file. Imports the texture (with
 *		one frame) associated to it.
 * 
 * @param mlx 
 * @param textures_group 
 * @param file_name pointer to the name of the file, *file_name is moved in the
 *				texture 
 * @return t_bool SUCCESS if texture imported, *file_name set to NULL to avoid
 *				future free
 */
static t_bool	_in_2_textu_group_init_from_file(void *mlx,
	t_group_of_textures *textures_group, char **file_name)
{
	char	**line_arg;

	textures_group->textures_array = ft_calloc(2, sizeof(t_animated_texture *));
	if (!textures_group->textures_array)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	line_arg = (char *[2]){*file_name, NULL};
	if (in_2_anim_textu_init(mlx, textures_group->textures_array, line_arg)
		== FAIL)
		return (free(textures_group->textures_array), FAIL);
	*file_name = NULL;
	textures_group->group_len = 1;
	return (SUCCESS);
}
