/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_group_of_textures_dir.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:14:50 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:03:32 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

static t_bool	_in_2_textu_group_dir_import_all_textures(void *mlx,
					t_group_of_textures	*textures_group, char *dir_name);
static t_bool	_in_2_textu_group_dir_import_one_texture(void *mlx,
					char *dir_parent_name, t_animated_texture **texture_dst,
					struct dirent *elem);

/**
 * @brief inits the texture group corresponding to the given directory.
 *		It will generate a table of pointer of t_animated_textures based on this
 *		repo content:
 *		- *.xpm at the root of the repo are considered as independant static
 *			textures (animated textures with one frame)
 *		- each root subdirectories can be describing one animated texture if it
 *			contains:
 *			-- at least one *.xpm file
 *			-- one file named as defined by TEXTURE_PARAMETERS_FILE_NAME which
 *				two first lines are the delay between each frames in ms and the
 *				pause delay in ms at the end of the frames cycle.
 * 
 * @param mlx 
 * @param textures_group 
 * @param dir_name 
 * @return t_bool	SUCCESS if the texture group has been succesfully
 *						imported.
 *					FAIL if failure in the texture importation (allocation,
 *						file/reporitory opening, ...). Error msg displayed.
 */
t_bool	in_2_textu_group_init_from_dir(void *mlx,
	t_group_of_textures *textures_group, char *dir_name)
{
	if (in_2_textu_group_dir_count_textures(dir_name,
			&textures_group->group_len) == FAIL)
		return (FAIL);
	if (!textures_group->group_len)
		return (to_error_msg(MSG_NO_XPM_IN_FOLDER), FAIL);
	if (ft_strlen(dir_name) > 1
		&& dir_name[ft_strlen(dir_name) - 1] == '/')
		dir_name[ft_strlen(dir_name) - 1] = 0;
	textures_group->textures_array = ft_calloc(textures_group->group_len + 1,
			sizeof(t_animated_texture *));
	if (!textures_group->textures_array)
		return (to_error_msg(MSG_BAD_ALLOC), textures_group->group_len = 0,
			FAIL);
	if (_in_2_textu_group_dir_import_all_textures(mlx, textures_group,
			dir_name) == FAIL)
		return (FAIL);
	in_2_textu_group_dir_sort_anim_textures(textures_group);
	return (SUCCESS);
}

/**
 * @brief given a directory name, imports all the textures it contains in the
 *	given texture_group textures array
 * 
 * @param mlx 
 * @param textures_group 
 * @param dir_name name of the directory containing the textures
 * @return t_bool	SUCCESS if all the textures have been successfully imported
 *					FAIL if error during the importation, error msg displayed
 */
static t_bool	_in_2_textu_group_dir_import_all_textures(void *mlx,
	t_group_of_textures	*textures_group, char *dir_name)
{
	DIR					*dir;
	struct dirent		*elem;
	size_t				i;

	dir = opendir(dir_name);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	i = 0;
	elem = readdir(dir);
	while (elem)
	{
		if (_in_2_textu_group_dir_import_one_texture(mlx, dir_name,
				&textures_group->textures_array[i], elem)
			== FAIL)
			return (closedir(dir), FAIL);
		if (textures_group->textures_array[i])
			++i;
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
 *						**texture_dst or if it is not a texture.
 */
static t_bool	_in_2_textu_group_dir_import_one_texture(void *mlx,
	char *dir_parent_name, t_animated_texture **texture_dst,
	struct dirent *elem)
{
	char			**line_arg;
	bool			subdir_is_texture;

	if (in_2_utiles_is_xpm_file(elem))
		line_arg = in_2_textu_group_dir_line_arg_from_subfile(dir_parent_name,
				elem->d_name);
	else if (elem->d_type == DT_DIR && *elem->d_name != '.')
	{
		if (in_2_textu_group_dir_check_subdir_contains_texture(dir_parent_name,
				elem->d_name, &subdir_is_texture) == FAIL)
			return (FAIL);
		if (!subdir_is_texture)
			return (SUCCESS);
		line_arg = in_2_textu_group_dir_line_arg_from_subdir(dir_parent_name,
				elem->d_name);
	}
	else
		return (SUCCESS);
	if (!line_arg
		|| in_2_anim_textu_init(mlx, texture_dst, line_arg) == FAIL)
		return (ft_strlst_free(line_arg), FAIL);
	ft_strlst_free(line_arg);
	return (SUCCESS);
}

#endif

//tests
/*

static void		_tests_in_2_textu_group_dir_import_one_texture(int ac,
					char **av, char **env);
static void		_tests_in_2_textu_group_init_from_dir(int ac, char **av,
					char **env);

int	main(int ac, char **av, char **env)
{
	(void)env;
	if (false)
		_tests_in_2_textu_group_dir_import_one_texture(ac, av, env);
	if (true)
		_tests_in_2_textu_group_init_from_dir(ac, av, env);
	return (0);
}

static void _tests_display_anim_texture_content(t_animated_texture *texture)
{
	unsigned int	i;

	if (!texture)
	{
		printf("No texture to display\n");
		return ;
	}

	printf(" - frame_number : %u\n", texture->frame_number);
	printf(" - frame_ms : %u\n", texture->frame_ms);
	printf(" - frame_pause_ms : %u\n", texture->frame_pause_ms);
	printf(" - frame_cycle_short : %u\n",
		texture->frame_cycle_short);
	printf(" - frame_cycle_long : %u\n", texture->frame_cycle_long);
	printf(" - frame_array paths:\n");
	i = 0;
	while (i < texture->frame_number)
	{
		printf("   - %d: {%s}\n", i, texture->frame_array[i].path);
		++i;
	}
}

static void	_tests_in_2_textu_group_dir_import_one_texture(int ac, char **av,
	char **env)
{
	void				*mlx;
	char				*dir_parent_name;
	t_animated_texture	*texture;
	DIR					*dir;
	struct dirent		*elem;

	printf("==== Test: _in_2_textu_group_dir_import_one_texture ====\n");
	if (ac != 2)
	{
		printf("Need 1 arg: dir_name (contining different repo/files that will \
be given to _in_2_textu_group_dir_import_one_texture)\n");
		return ;
	}
	(void)env;
	mlx = mlx_init();
	dir_parent_name = av[1];
	dir = opendir(dir_parent_name);
	if (!dir)
	{
		printf("Error: wrong directory given in \
_tests_in_2_textu_group_dir_import_one_texture\n");
		return ;
	}
	elem = readdir(dir);
	while (elem)
	{
		printf("=== Elem \"%s\" ===\n", elem->d_name);
		texture = 0;
		if (_in_2_textu_group_dir_import_one_texture(mlx, dir_parent_name,
				&texture, elem) == FAIL)
		{
			printf("FAIL\n");
			break ;
		}
		_tests_display_anim_texture_content(texture);
		//no texture destroy for now
		printf("\n");
		elem = readdir(dir);
	}
	closedir(dir);
	printf("---- End: _in_2_textu_group_dir_import_one_texture ----\n\n");
}

static void	_tests_in_2_textu_group_init_from_dir(int ac, char **av,
	char **env)
{
	void				*mlx;
	t_texture_pack		texture_pack = {0};
	t_group_of_textures	*texture_gp = &texture_pack.wall_n;
	unsigned int		i;

	printf("==== Test: in_2_textu_group_init_from_dir ====\n");
	if (ac != 2)
	{
		printf("Needs 1 arg: dir_name (contining different repo/files that will \
be given to in_2_textu_group_init_from_dir()\n");
		return ;
	}
	(void)env;
	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init fail\n");
		return ;
	}
	if (in_2_textu_group_init_from_dir(mlx, texture_gp, av[1]) == FAIL)
	{
		printf("\e[103mReturn:\e[0m FAIL\n");
		return ;
	}
	printf("\e[103mreturn:\e[0m SUCCESS\n");
	printf("\e[103mgoup_len:\e[0m %u\n\n", texture_gp->group_len);
	printf("\e[103mTextures:\e[0m\n");
	i = 0;
	while (i < texture_gp->group_len)
	{
		_tests_display_anim_texture_content(texture_gp->textures_array[i]);
		printf("\n");
		++i;
	}
	end_destroy_texture_pack(mlx, &texture_pack);
	mlx_destroy_display(mlx);
	free(mlx);
}

*/