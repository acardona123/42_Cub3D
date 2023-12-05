/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_group_of_textures_dir_su        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:01:44 by acardona          #+#    #+#             */
/*   Updated: 2023/12/05 19:10:20 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief counts if the given repository contains at least one valid texture,
 *	which is ether:
 *	- a .xpm file at the root of this directory (later considered
 *	as a static texture)
 *	- a subdirectory containing at least one .xpm file and, if there are
 *	multiple .xpm files, a file named like TEXTURE_PARAMETERS_FILE_NAME define
 *	(later used for describing the frame rates). Those .xpm in the subdirectory
 *	are the frames of one animated textured.
 *	The number of valid textures is stored in cpt_textures
 * 
 * @param dir_name the name of the directory to check
 * @param cpt_textures its value is updated to the number of textures found in
 *		the directory
 * @return t_bool	SUCCESS if the directory has successfully been opened and
 *						verified, cpt updated 
 *					FAIL in case of opendir failure, err msg displayed					
 */
t_bool	in_2_textu_group_dir_count_textures(char *dir_name,
	unsigned int *cpt_textures)
{
	DIR				*dir;
	struct dirent	*elem;
	bool			elem_is_texture;

	*cpt_textures = 0;
	dir = opendir(dir_name);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	elem = readdir(dir);
	while (elem)
	{
		elem_is_texture = false;
		if (in_2_utiles_is_xpm_file(elem))
			elem_is_texture = true;
		else if (elem->d_type == DT_DIR && *elem->d_name != '.'
			&& in_2_textu_group_dir_check_subdir_contains_texture
			(dir_name, elem->d_name, &elem_is_texture) == FAIL)
			return (closedir(dir), FAIL);
		*cpt_textures += elem_is_texture;
		elem = readdir(dir);
	}
	closedir(dir);
	return (SUCCESS);
}

/**
 * @brief checks if a given directory contains what is requiered to define a
 *	texture:
 *	- at least one .xpm file
 *	- a file named as TEXTURE_PARAMETERS_FILE_NAME define
 * 
 * @param dir_name 
 * @param subdir_name 
 * @param cpt_textures updated if success
 * @return t_bool	FAIL if opendir fail, err msg displayed
 *					SUCCESS if opendir worked, if the subdir contains a valid
 *					texture ( at least one .xpm file and, if there are
 *					multiple .xpm files, a file named as 
 *					TEXTURE_PARAMETERS_FILE_NAME)
 */
t_bool	in_2_textu_group_dir_check_subdir_contains_texture(char *dir_name,
	char *subdir_name, bool *subdir_contains_textures)
{
	DIR				*dir;
	struct dirent	*elem;
	int				cpt_xpm;
	int				cpt_data_txt;

	subdir_name = to_file_build_path(dir_name, subdir_name, NULL, NULL);
	if (!subdir_name)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	dir = opendir(subdir_name);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), free(subdir_name), FAIL);
	cpt_xpm = 0;
	cpt_data_txt = 0;
	elem = readdir(dir);
	while (elem)
	{
		cpt_xpm += in_2_utiles_is_xpm_file(elem);
		cpt_data_txt += (elem->d_type == DT_REG
				&& !ft_strcmp(elem->d_name, TEXTURE_PARAMETERS_FILE_NAME));
		elem = readdir(dir);
	}
	if (cpt_xpm && cpt_data_txt != 1)
		to_warning_msg(MSG_WARNING_TEXTURE_DATA_MISSING);
	*subdir_contains_textures = (cpt_xpm && cpt_data_txt == 1);
	return (closedir(dir), free(subdir_name), SUCCESS);
}

/**
 * @brief used in directories containing multiple subdirectoris of textures 
 *		elements (examples: leaks/crashes subdirectories), applied on the
 *		subdirectories to generates the char **line_arg requiered to call the
 *		in_2_anim_textu_init function with the texture informations in
 *		dir_name/TEXTURE_PARAMETERS_FILE_NAME
 * 
 * @param dir_parent_name 
 * @param dir_name 
 * @return char**	success: the line_arg for in_2_anim_textu_init
 *					error (malloc/open): NULL, error msg display
 */
char	**in_2_textu_group_dir_line_arg_from_subdir(char *dir_parent_name,
	char *dir_name)
{
	char	**arg;
	int		fd;
	char	*data_file;

	data_file = to_file_build_path(dir_parent_name, dir_name,
			TEXTURE_PARAMETERS_FILE_NAME, NULL);
	if (!data_file)
		return (to_error_msg(MSG_BAD_ALLOC), NULL);
	fd = open(data_file, O_RDONLY);
	free(data_file);
	if (fd == -1)
		return (to_error_msg(MSG_ERR_OPEN_TEXTURE_DATA), NULL);
	arg = ft_calloc(4, sizeof(char *));
	if (!arg)
		return (to_error_msg(MSG_BAD_ALLOC), close (fd), NULL);
	arg[0] = to_file_build_path(dir_parent_name, dir_name, NULL, NULL);
	if (!arg[0])
		return (to_error_msg(MSG_BAD_ALLOC), close(fd), ft_tabfree(arg), NULL);
	if (to_get_next_line(fd, &arg[1]))
		return (close(fd), ft_tabfree(arg), NULL);
	if (arg[1] && to_get_next_line(fd, &arg[2]))
		return (close(fd), ft_tabfree(arg), NULL);
	if (!arg[1] || !arg[2])
		return (to_error_msg(MSG_FILE_EOF), close(fd), ft_tabfree(arg), NULL);
	return (to_get_next_line(-1, NULL), close(fd), arg);
}

/**
 * @brief used for texure file (.xpm) directly in a texture root directory
 *		(examples: leaks/texture1.xpm):
 *		generates the char **line_arg requiered to call the
 *		in_2_anim_textu_init function
 * 
 * @param dir_name 
 * @param file_name 
 * @return char**	success: the line_arg for in_2_anim_textu_init
 *					error (malloc/open): NULL, error msg display
 */
char	**in_2_textu_group_dir_line_arg_from_subfile(char *dir_name,
	char *file_name)
{
	char	**arg;

	arg = ft_calloc(2, sizeof(char *));
	if (!arg)
		return (to_error_msg(MSG_BAD_ALLOC), NULL);
	arg[0] = to_file_build_path(dir_name, file_name, NULL, NULL);
	if (!arg[0])
		return (to_error_msg(MSG_BAD_ALLOC), free(arg), NULL);
	return (arg);
}

/**
 * @brief sorts all animated textures of the group based on the name of their
 *		first frame path (increasing ascii)
 * 
 * @param group 
 */
void	in_2_textu_group_dir_sort_anim_textures(t_group_of_textures *group)
{
	unsigned int		i;
	unsigned int		j;
	t_animated_texture	*tmp;

	i = 1;
	while (i < group->group_len)
	{
		j = i + 1;
		while (--j)
		{
			if (ft_strcmp(group->textures_array[j]->frame_array[0].path,
					group->textures_array[j - 1]->frame_array[0].path) < 0)
			{
				tmp = group->textures_array[j];
				group->textures_array[j] = group->textures_array[j - 1];
				group->textures_array[j - 1] = tmp;
			}
		}
		++i;
	}
}

#endif

//tests
/*

static void	_tests_in_2_textu_group_dir_count_textures(int ac, char **av,
				char **env);
static void	_tests_in_2_textu_group_dir_line_arg_from_subdir(int ac, char **av,
				char **env);

int main(int ac, char **av, char **env)
{
	(void)env;
	if (false)
		_tests_in_2_textu_group_dir_count_textures(ac, av, env);
	if (false)
		_tests_in_2_textu_group_dir_line_arg_from_subdir(ac, av, env);
	return (0);
}

static void	_tests_in_2_textu_group_dir_count_textures(int ac, char **av,
	char **env)
{
	size_t	cpt_textures;
	char	*dir_name;

	printf("==== Test: testsin_2_textu_group_dir_count_textures ====\n");
	if (ac != 2)
	{
		printf("Need 1 arg: dir_name\n");
		return ;
	}
	(void)env;
	dir_name = av[1];
	printf("Directory tested: {%s}\n", dir_name);
	if (in_2_textu_group_dir_count_textures(dir_name, &cpt_textures) == FAIL)
		printf("return : FAIL\n");
	else
		printf("return SUCCESS: cpt_texture = %zu\n", cpt_textures);
	printf("---- End: testsin_2_textu_group_dir_count_textures ----\n\n");
}

static void	_tests_in_2_textu_group_dir_line_arg_from_subdir(int ac, char **av,
	char **env)
{
	char	*dir_parent_name;
	char	*dir_name;
	char	**line_arg;
	char	**line_elem;

	printf("==== Test: _in_2_textu_group_dir_line_arg_from_subdir ====\n");
	if (ac != 3)
	{
		printf("Need 2 arg: dir_parent_name dir_name\n");
		return ;
	}
	(void)env;
	dir_parent_name = av[1];
	dir_name = av[2];
	printf("Directory tested: {%s/%s}\n", dir_parent_name, dir_name);
	line_arg = _in_2_textu_group_dir_line_arg_from_subdir(dir_parent_name,
		dir_name);
	if (line_arg == NULL)
		printf("return : NULL\n");
	else
	{
		line_elem = line_arg;
		while (*line_elem)
		{
			printf("\"%s\" ", *line_elem);
			++line_elem;
		}
		printf("(null)\n");
		ft_strlst_free(line_arg);
	}
	printf("---- End: _in_2_textu_group_dir_line_arg_from_subdir ----\n\n");
}
*/