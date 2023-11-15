/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_random_screen.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:14:50 by acardona          #+#    #+#             */
/*   Updated: 2023/11/15 05:22:33 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static t_bool	_in_2_count_textures(char *dir_name,
					unsigned int *cpt_textures);
static t_bool	_in_2_check_subdir_contains_texture(char *subdir_name,
					unsigned int *cpt);
static t_bool	_in_2_import_all_textures(void *mlx,
					t_animated_texture **textures, char *dir_name,
					unsigned int number_of_textures);
static char		**_in_2_line_arg_from_directory(char *dir_parent_name,
					char *dir_name);
static char		**_in_2_line_arg_from_file(char *dir_parent_name,
					char *dir_name);

t_bool	in_2_anim_textu_random_screen(void *mlx, t_animated_texture **textures,
	char **line_arg)
{
	unsigned int	cpt_textures;

	if (_in_2_count_textures(line_arg[0], &cpt_textures) == FAIL)
		return (FAIL);
	if (!cpt_textures)
		return (SUCCESS);
	if (*line_arg[0] != '/' && line_arg[0][ft_strlen(line_arg[0]) - 1] == '/')
		line_arg[0][ft_strlen(line_arg[0]) - 1] = 0;
	*textures = ft_calloc(cpt_textures + 1, sizeof(t_animated_texture *));
	if (!*textures)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	
}

static t_bool	_in_2_count_textures(char *dir_name,
	unsigned int *cpt_textures)
{
	DIR				*dir;
	struct dirent	*elem;
	int				cpt_xpm_in_dir;

	*cpt_textures = 0;
	dir = opendir(dir_name);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	elem = readdir(dir);
	while (elem)
	{
		if ((elem->d_type == DT_REG && ft_strlen(elem->d_name) >= 4
				&& !ft_strcmp(elem->d_name + ft_strlen(elem->d_name) - 4,
					".xpm")))
			++*cpt_textures;
		if (elem->d_type == DT_DIR && _in_2_check_subdir_contains_texture
			(elem->d_name, cpt_textures) == FAIL)
			return (closedir(dir), FAIL);
		elem = readdir(dir);
	}
	closedir(dir);
	if (!*cpt_textures)
		return (to_error_msg(MSG_NO_XPM_IN_FOLDER), FAIL);
	return (SUCCESS);
}

/**
 * @brief checks if a given directories contains what is requiered to define a
 *	texture: at least one .xpm file and a file named frames_data.txt
 *	if som add 1 to 
 * 
 * @param subdir_name 
 * @param cpt 
 * @return t_bool 
 */
static t_bool	_in_2_check_subdir_contains_texture(char *subdir_name,
	unsigned int *cpt)
{
	DIR				*dir;
	struct dirent	*elem;
	bool			contains_xpm;
	int				contains_data_txt;

	dir = opendir(subdir_name);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	contains_xpm = false;
	contains_data_txt = 0;
	elem = readdir(dir);
	while (elem)
	{
		if ((elem->d_type == DT_REG && ft_strlen(elem->d_name) >= 4
				&& !ft_strcmp(elem->d_name + ft_strlen(elem->d_name) - 4,
					".xpm")))
			contains_xpm = true;
		if (elem->d_type == DT_REG
			&& !ft_strcmp(elem->d_name, "frames_data.txt"))
			++contains_data_txt;
		elem = readdir(dir);
	}
	closedir(dir);
	return (*cpt += (contains_xpm && (contains_data_txt == 1)), SUCCESS);
}

static t_bool	_in_2_import_all_textures(void *mlx,
	t_animated_texture **textures, char *dir_name,
	unsigned int number_of_textures)
{
	DIR				*dir;
	struct dirent	*elem;
	unsigned int	textu_idx;
	int				is_texture;

	textu_idx = 0;
		dir = opendir(dir_name);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	elem = readdir(dir);
	while (elem)
	{
		
	}
}
/**
 * @brief 
 * 
 * @param mlx 
 * @param textures 
 * @param textu_idx 
 * @param elem 
 * @return t_bool 
 */
static t_bool	_in_2_import_one_texture(void *mlx, char *dir_parent_name, 
	t_animated_texture **textures, unsigned int *textu_idx,
	struct dirent *elem)
{
	unsigned int	cpt;
	char			**line_arg;

	cpt = 0;
	if ((elem->d_type == DT_REG && ft_strlen(elem->d_name) >= 4
			&& !ft_strcmp(elem->d_name + ft_strlen(elem->d_name) - 4, ".xpm")))
		line_arg = _in_2_line_arg_from_file(dir_parent_name, elem->d_name);
	else if (elem->d_type == DT_DIR)
	{
		if (_in_2_check_subdir_contains_texture(elem->d_name, &cpt) == FAIL)
			return (FAIL);
		if (cpt == 0)
			return (SUCCESS);
		line_arg = _in_2_line_arg_from_directory(dir_parent_name, elem->d_name);
	}
	else
		return (SUCCESS);
	if (!line_arg
		|| in_2_anim_textu_init(mlx, textures + *textu_idx, line_arg) == FAIL)
		return (ft_strlst_free(line_arg), FAIL);
	ft_strlst_free(line_arg);
	++(*textu_idx);
	return (SUCCESS);
}

/**
 * @brief used in directories containing random-screen textures elements
 *		(examples: leaks/crashes subdirectories):
 *		generates the char **line_arg requiered to call the
 *		in_2_anim_textu_init function with the texture informations in
 *		dir_name/frames_data.txt
 * 
 * @param dir_parent_name 
 * @param dir_name 
 * @return char**	success: the line_arg for in_2_anim_textu_init
 *					error (malloc/open): NULL, error msg display
 */
static char	**_in_2_line_arg_from_directory(char *dir_parent_name,
	char *dir_name)
{
	char	**arg;
	int		fd;
	char	*data_file;

	data_file = ft_strjoin(dir_name, "/frames_data.txt");
	if (!data_file)
		return (to_error_msg(MSG_BAD_ALLOC), NULL);
	fd = open(data_file, O_RDONLY);
	free(data_file);
	if (fd == -1)
		return (to_error_msg(MSG_MAP_OPEN_FAIL), NULL);
	arg = ft_calloc(4, sizeof(char *));
	if (!arg)
		return (to_error_msg(MSG_BAD_ALLOC), close (fd), NULL);
	arg[0] = ft_strjoin3(dir_parent_name, "/", dir_name);
	if (!arg)
		return (to_error_msg(MSG_BAD_ALLOC), close(fd), ft_tabfree(arg), NULL);
	arg[1] = get_next_line(fd);
	if (!arg[1])
		return (to_error_msg(MSG_BAD_ALLOC), close(fd), ft_tabfree(arg), NULL);
	arg[2] = get_next_line(fd);
	if (!arg[2])
		return (to_error_msg(MSG_BAD_ALLOC), close(fd), ft_tabfree(arg), NULL);
	close(fd);
	return (arg);
}

/**
 * @brief used for texure file (.xpm) directly in a random-screen textures
 *		directory (examples: leaks/crashes ):
 *		generates the char **line_arg requiered to call the
 *		in_2_anim_textu_init function
 * 
 * @param dir_parent_name 
 * @param dir_name 
 * @return char**	success: the line_arg for in_2_anim_textu_init
 *					error (malloc/open): NULL, error msg display
 */
static char	**_in_2_line_arg_from_file(char *dir_parent_name, char *dir_name)
{
	char	**arg;
	char	*file_name;

	arg = ft_calloc(2, sizeof(char *));
	if (!arg)
		return (to_error_msg(MSG_BAD_ALLOC), NULL);
	arg[0] = ft_strjoin3(dir_parent_name, "/", dir_name);
	if (!arg[0])
		return (to_error_msg(MSG_BAD_ALLOC), free(arg), NULL);
	return (arg);
}
