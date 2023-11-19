/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_random_screen.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:14:50 by acardona          #+#    #+#             */
/*   Updated: 2023/11/19 01:45:05 by acardona         ###   ########.fr       */
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
static t_bool	_in_2_import_one_texture(void *mlx, char *dir_parent_name,
					t_animated_texture ***texture_dst, struct dirent *elem);
static char		**_in_2_line_arg_from_directory(char *dir_parent_name,
					char *dir_name);
static char		**_in_2_line_arg_from_file(char *dir_parent_name,
					char *dir_name);

t_bool	in_2_anim_textu_random_screen(void *mlx, t_animated_texture ***textures,
	char **line_arg)
{
	unsigned int	cpt_textures;

	if (_in_2_count_textures(line_arg[0], &cpt_textures) == FAIL)
		return (FAIL);
	if (!cpt_textures)
		return (SUCCESS);
	if (ft_strlen(line_arg[0]) > 1
		&& line_arg[0][ft_strlen(line_arg[0]) - 1] == '/')
		line_arg[0][ft_strlen(line_arg[0]) - 1] = 0;
	**textures = ft_calloc(cpt_textures + 1, sizeof(t_animated_texture *));
	if (!**textures)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	return (_in_2_import_all_textures(mlx, *textures, line_arg[0],
			cpt_textures));
}

/**
 * @brief counts if the given repository contains at least one valid texture,
 *	which is ether:
 *	- a .xpm file at the root of this directory (later considered
 *	as a static texture)
 *	- a subdirectory containing at least one .xpm file and, if there are
 *	multiple .xpm files, a file named frames_data.txt (later used for describing
 *	the frame rates of the animated textured composed by the .xpm files of the
 *	subdirectory.
*	The number of valid textures is stored in cpt_textures
 * 
 * @param dir_name the name of the directory to check
 * @param cpt_textures its value is updated to the number of textures found in
 *		the directory
 * @return t_bool	SUCCESS if the directory has successfully been opened and
 *						valid textures have been found in it. In this case
 *						*cpt_textures is the number of texture ( > 0 )
					FAIL in case of opendir failure
					
 */
static t_bool	_in_2_count_textures(char *dir_name, unsigned int *cpt_textures)
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
		if (in_2_tools_is_xpm_file(elem))
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
 * @param cpt_textures 
 * @return t_bool	FAIL if opendir fail, err msg displayed
 *					SUCCESS if opendir worked, if the subdir contains a valid
 *					texture ( at least one .xpm file and, if there are
 *					multiple .xpm files, a file named frames_data.txt)
 */
static t_bool	_in_2_check_subdir_contains_texture(char *subdir_name,
	unsigned int *cpt_textures)
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
		if (in_2_tools_is_xpm_file(elem))
			contains_xpm = true;
		if (elem->d_type == DT_REG
			&& !ft_strcmp(elem->d_name, "frames_data.txt"))
			++contains_data_txt;
		elem = readdir(dir);
	}
	closedir(dir);
	if (contains_xpm && (contains_data_txt <= 1
			&& (contains_xpm == 1 || contains_data_txt)))
		++cpt_textures;
	return (SUCCESS);
}

static t_bool	_in_2_import_all_textures(void *mlx,
	t_animated_texture **textures, char *dir_name,
	unsigned int number_of_textures)
{
	DIR					*dir;
	struct dirent		*elem;
	t_animated_texture	**next_texture_dest;

	dir = opendir(dir_name);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	next_texture_dest = textures;
	elem = readdir(dir);
	while (elem)
	{
		elem = readdir(dir);
		if (_in_2_import_one_texture(mlx, dir_name, &next_texture_dest, elem)
			== FAIL)
			return (closedir(dir), FAIL);
		elem = readdir(dir);
	}
	closedir(dir);
	return (SUCCESS);
}

/**
 * @brief if elem is a valid texture, imports it in the table of animated
 *		textures *texture_dst and moves texture_dst to the next index in the 
 *		table
 * texture_dst
 * @param mlx 
 * @param dir_parent_name 
 * @param texture_dst pointer to where the pointer of the animated texture will
 *				be saved
 * @param elem the element of a directory that we try to import
 * @return t_bool	FAIL if elem is a valid texture but there was an error in
 *						 its importation. Error msg displayed.
 *					SUCCESS if elem is a texture successfully imported in
 *						**texture_dst.
 */
static t_bool	_in_2_import_one_texture(void *mlx, char *dir_parent_name,
	t_animated_texture ***texture_dst, struct dirent *elem)
{
	unsigned int	cpt;
	char			**line_arg;

	cpt = 0;
	if (in_2_tools_is_xpm_file(elem))
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
		|| in_2_anim_textu_init(mlx, *(texture_dst++), line_arg) == FAIL)
		return (ft_strlst_free(line_arg), FAIL);
	ft_strlst_free(line_arg);
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
	if (!arg[0])
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


