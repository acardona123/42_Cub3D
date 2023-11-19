/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_random_screen.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:14:50 by acardona          #+#    #+#             */
/*   Updated: 2023/11/19 05:29:22 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static t_bool	_in_2_count_textures(char *dir_name,
					unsigned int *cpt_textures);
static t_bool	_in_2_check_subdir_contains_texture(char *parent_dir,
					char *subdir_name, bool *subdir_contains_textures);
static t_bool	_in_2_import_all_textures(void *mlx,
					t_animated_texture **textures, char *dir_name);
static t_bool	_in_2_import_one_texture(void *mlx, char *dir_parent_name,
					t_animated_texture ***texture_dst, struct dirent *elem);
static char		**_in_2_line_arg_from_subdir(char *dir_parent_name,
					char *dir_name);
static char		**_in_2_line_arg_from_file(char *dir_parent_name,
					char *file_name);

t_bool	in_2_anim_textu_random_screen(void *mlx, t_animated_texture ***textures,
	char **line_arg)
{
	unsigned int	cpt_textures;

	if (_in_2_count_textures(line_arg[0], &cpt_textures) == FAIL)
		return (FAIL);
	if (!cpt_textures)
		return (to_error_msg(MSG_NO_XPM_IN_FOLDER), FAIL);
	if (ft_strlen(line_arg[0]) > 1
		&& line_arg[0][ft_strlen(line_arg[0]) - 1] == '/')
		line_arg[0][ft_strlen(line_arg[0]) - 1] = 0;
	**textures = ft_calloc(cpt_textures + 1, sizeof(t_animated_texture *));
	if (!**textures)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	return (_in_2_import_all_textures(mlx, *textures, line_arg[0]));
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
 *						verified
					FAIL in case of opendir failure, err msg displayed
					
 */
static t_bool	_in_2_count_textures(char *dir_name, unsigned int *cpt_textures)
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
		// printf("\n%s:\n", elem->d_name);//
		elem_is_texture = false;
		if (in_2_tools_is_xpm_file(elem))
			elem_is_texture = true;
		else if (elem->d_type == DT_DIR && *elem->d_name != '.'
			&& _in_2_check_subdir_contains_texture
			(dir_name, elem->d_name, &elem_is_texture) == FAIL)
			return (closedir(dir), FAIL);
		*cpt_textures += elem_is_texture;
		// printf("%s-> cpt = %u\n", elem->d_name, *cpt_textures);//
		elem = readdir(dir);
	}
	closedir(dir);
	return (SUCCESS);
}

/**
 * @brief checks if a given directories contains what is requiered to define a
 *	texture: at least one .xpm file and a file named frames_data.txt
 *	if som add 1 to 
 * 
 * @param parent_name 
 * @param subdir_name 
 * @param cpt_textures updated if success
 * @return t_bool	FAIL if opendir fail, err msg displayed
 *					SUCCESS if opendir worked, if the subdir contains a valid
 *					texture ( at least one .xpm file and, if there are
 *					multiple .xpm files, a file named frames_data.txt)
 */
static t_bool	_in_2_check_subdir_contains_texture(char *parent_dir,
	char *subdir_name, bool *subdir_contains_textures)
{
	DIR				*dir;
	struct dirent	*elem;
	int				cpt_xpm;
	int				cpt_data_txt;

	subdir_name = ft_strjoin3(parent_dir, "/", subdir_name);
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
		cpt_xpm += in_2_tools_is_xpm_file(elem);
		cpt_data_txt += (elem->d_type == DT_REG
				&& !ft_strcmp(elem->d_name, "frames_data.txt"));
		elem = readdir(dir);
	}
	if (cpt_xpm && !cpt_data_txt)
		to_warning_msg(MSG_WARNING_TEXTURE_DATA_MISSING);
	(*subdir_contains_textures) = (cpt_xpm && cpt_data_txt == 1);
	return (closedir(dir), free(subdir_name), SUCCESS);
}

static t_bool	_in_2_import_all_textures(void *mlx,
	t_animated_texture **textures, char *dir_name)
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
	char			**line_arg;
	bool			subdir_is_texture;

	if (in_2_tools_is_xpm_file(elem))
		line_arg = _in_2_line_arg_from_file(dir_parent_name, elem->d_name);
	else if (elem->d_type == DT_DIR && *elem->d_name != '.')
	{
		if (_in_2_check_subdir_contains_texture(dir_parent_name, elem->d_name,
				&subdir_is_texture) == FAIL)
			return (FAIL);
		if (!subdir_is_texture)
			return (SUCCESS);
		line_arg = _in_2_line_arg_from_subdir(dir_parent_name, elem->d_name);
	}
	else
		return (SUCCESS);
	if (!line_arg
		|| in_2_anim_textu_init(mlx, *texture_dst, line_arg) == FAIL)
		return (ft_strlst_free(line_arg), FAIL);
	++(*texture_dst);
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
static char	**_in_2_line_arg_from_subdir(char *dir_parent_name,
	char *dir_name)
{
	char	**arg;
	int		fd;
	char	*data_file;

	data_file = ft_strjoin4(dir_parent_name, "/", dir_name, "/frames_data.txt");
	// printf("data_file: {%s}\n", data_file);//
	if (!data_file)
		return (to_error_msg(MSG_BAD_ALLOC), NULL);
	fd = open(data_file, O_RDONLY);
	free(data_file);
	if (fd == -1)
		return (to_error_msg(MSG_ERR_OPEN_TEXTURE_DATA), NULL);
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
static char	**_in_2_line_arg_from_file(char *dir_parent_name, char *file_name)
{
	char	**arg;

	arg = ft_calloc(2, sizeof(char *));
	if (!arg)
		return (to_error_msg(MSG_BAD_ALLOC), NULL);
	arg[0] = ft_strjoin3(dir_parent_name, "/", file_name);
	if (!arg[0])
		return (to_error_msg(MSG_BAD_ALLOC), free(arg), NULL);
	return (arg);
}

//tests
// /*

static void _tests_in_2_count_textures(int ac, char **av, char **env);
static void	_tests_in_2_line_arg_from_subdir(int ac, char **av, char **env);
static void	_tests_in_2_import_one_texture(int ac, char **av, char **env);


int main(int ac, char **av, char **env)
{
	(void)env;
	if (false)
		_tests_in_2_count_textures(ac, av, env);
	if (false)
		_tests_in_2_line_arg_from_subdir(ac, av, env);
	if (true)
		_tests_in_2_import_one_texture(ac, av, env);
	return (0);
}

static void _tests_in_2_count_textures(int ac, char **av, char **env)
{
	unsigned int	cpt_textures;
	char			*dir_name;

	printf("==== Test: tests_in_2_count_textures ====\n");
	if (ac != 2)
	{
		printf("Need 1 arg: dir_name\n");
		return ;
	}
	(void)env;
	dir_name = av[1];
	printf("Directory tested: {%s}\n", dir_name);
	if (_in_2_count_textures(dir_name, &cpt_textures) == FAIL)
		printf("return : FAIL\n");
	else
		printf("return SUCCESS: cpt_texture = %u\n", cpt_textures);
	printf("---- End: tests_in_2_count_textures ----\n\n");
}

static void	_tests_in_2_line_arg_from_subdir(int ac, char **av, char **env)
{
	char	*dir_parent_name;
	char	*dir_name;
	char	**line_arg;
	char	**line_elem;

	printf("==== Test: _in_2_line_arg_from_subdir ====\n");
	if (ac != 3)
	{
		printf("Need 2 arg: dir_parent_name dir_name\n");
		return ;
	}
	(void)env;
	dir_parent_name = av[1];
	dir_name = av[2];
	printf("Directory tested: {%s/%s}\n", dir_parent_name, dir_name);
	line_arg = _in_2_line_arg_from_subdir(dir_parent_name, dir_name);
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
	printf("---- End: _in_2_line_arg_from_subdir ----\n\n");
}

static void	_tests_in_2_import_one_texture(int ac, char **av, char **env)
{
	void				*mlx;
	char				*dir_parent_name;
	t_animated_texture	**textures;
	t_animated_texture	**dst_text;
	DIR					*dir;
	struct dirent		*elem;
	
	printf("==== Test: _in_2_import_one_texture ====\n");
	if (ac != 2)
	{
		printf("Need 1 arg: dirt_name\n");
		return ;
	}
	(void)env;
	textures = ft_calloc(2, sizeof(t_animated_texture *));
	dst_text = textures;
	printf("textures: %p\n\n", textures);
	mlx = mlx_init();
	dir_parent_name = av[1];
	dir = opendir(dir_parent_name);
	elem = readdir(dir);
	while (elem)
	{
		printf("=== Elem \"%s\" ===\n", elem->d_name);
		dst_text = textures;
		*textures = 0;
		if (_in_2_import_one_texture(mlx, dir_parent_name, &dst_text, elem)
			== FAIL)
		{
			printf("FAIL\n");
			break ;
		}
		if (dst_text != textures)
		{
			printf("Texture imported:\n");
			printf(" - frame_number : %u\n", (**textures).frame_number);
			printf(" - frame_ms : %u\n", (**textures).frame_ms);
			printf(" - frame_pause_ms : %u\n", (**textures).frame_pause_ms);
			printf(" - frame_cycle_short : %u\n",
				(**textures).frame_cycle_short);
			printf(" - frame_cycle_long : %u\n", (**textures).frame_cycle_long);
			printf(" frame_array first path: {%s}\n",
				(**textures).frame_array[0].path);
		}
		printf("\n");
		elem = readdir(dir);
	}
	closedir(dir);
	//no free for now
	printf("---- End: _in_2_import_one_texture ----\n\n");
}

// */