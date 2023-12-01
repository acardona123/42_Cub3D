/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_animated_texture.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 01:53:53 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:19:58 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static t_bool	in_2_anim_textu_init_file(void *mlx,
					t_animated_texture *texture, char **line_arg);

#ifdef BONUS

static t_bool	_in_2_anim_textu_init_folder(void *mlx,
					t_animated_texture *texture, char **line_arg);

/**
 * @brief initializes the t_animated_texture structure of a texture based on a
*	fragmented line of the input file. Two possible syntaxes:
*	unanimated texture (stored as animated with only one static textu):
*		"elem_acronym" "text_img_path.xpm"
*	animated texture:
*		"elem_acronym" "text_repo_containing_img" "frame_ms" "frame_pause_ms"
 * 
 * @param texture 
 * @param line_arg the line of arg starting AFTER the accronyme
 * @return SUCCESS (textures successfully loaded, line_arg updated to extract
 *				line_arg[0] form it (to avoid it being freed))
 * @return FAIL (err msg displayed. no argument freed)
 */
t_bool	in_2_anim_textu_init(void *mlx, t_animated_texture **texture,
	char **line_arg)
{
	if (*texture)
		return (to_error_msg(MSG_TEXTURE_MULTIPLE_DEF), FAIL);
	*texture = ft_calloc(1, sizeof(t_animated_texture));
	if (!texture)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	if (ft_tablen(line_arg) == 1)
		return (in_2_anim_textu_init_file(mlx, *texture, line_arg));
	else if (ft_tablen(line_arg) == 3)
		return (_in_2_anim_textu_init_folder(mlx, *texture, line_arg));
	return (to_error_msg(MSG_WRONG_LINE_FORMAT), FAIL);
}

#else

/**
 * @brief initializes the t_animated_texture structure of a texture based on a
*	fragmented line of the input file. One possible syntaxes only:
*	static texture (stored as animated with only one static textu):
*		"elem_acronym" "text_img_path.xpm"
 * 
 * @param mlx 
 * @param texture 
 * @param line_arg the line of arg starting AFTER the accronyme
 * @return SUCCESS (textures successfully loaded, line_arg updated to extract
 *				line_arg[0] form it (to avoid it being freed))
 * @return FAIL (err msg displayed. no argument freed)
 */
t_bool	in_2_anim_textu_init(void *mlx, t_animated_texture **texture,
	char **line_arg)
{
	if (*texture)
		return (to_error_msg(MSG_TEXTURE_MULTIPLE_DEF), FAIL);
	*texture = ft_calloc(1, sizeof(t_animated_texture));
	if (!texture)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	if (ft_tablen(line_arg) == 1)
		return (in_2_anim_textu_init_file(mlx, *texture, line_arg));
	return (to_error_msg(MSG_WRONG_LINE_FORMAT), FAIL);
}

#endif

/**
 * @brief generates the t_animated_texture when only one path is given
 *		(without parameters for frames rate or so) => this path must be directly
 *		the .xpm file path
 * 
 * @param mlx
 * @param texture struct to fill
 * @param line_arg splited line of the input file to import, starting AFTER the
 *		accronym
 * @return SUCCESS: texture successfully imported, no line_arg freed (but arg[0]
 *		extracted from line_arg)
 * @return FAIL: err msg displayed, no arg freed
 */
static t_bool	in_2_anim_textu_init_file(void *mlx,
	t_animated_texture *texture, char **line_arg)
{
	texture->frame_array = ft_calloc (1, sizeof(t_static_texture));
	if (!texture->frame_array)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	texture->frame_number = 1;
	texture->frame_ms = 0;
	texture->frame_pause_ms = 0;
	texture->frame_cycle_short = 0;
	texture->frame_cycle_long = INT_MAX / 2;
	texture->frame_array[0] = (t_static_texture){line_arg[0], 0, 0, .0,
		(t_data){0}};
	if (in_2_static_texture_init_one(mlx, &texture->frame_array[0],
			line_arg[0]) == FAIL)
	{
		free(texture->frame_array);
		texture->frame_array = NULL;
		return (FAIL);
	}
	line_arg[0] = line_arg[ft_tablen(line_arg) - 1];
	line_arg[ft_tablen(line_arg) - 1] = NULL;
	return (SUCCESS);
}

#ifdef BONUS

static t_bool	_in_2_get_textures_from_directory(void *mlx, DIR *dir,
					char *dir_name, t_animated_texture *tex);

/**
 * @brief fills t_animated_texture structure based on the line_arg elements:
 *	"elem_acronym" "text_repo_containing_img" "frame_ms" "frame_pause_ms"
 * @param mlx 
 * @param texture 
 * @param line_arg 
 * @return SUCCESS: textures successfully imported, no arg freed
 * @return FAIL : err msg displayed, no arg freed
 */
static t_bool	_in_2_anim_textu_init_folder(void *mlx,
	t_animated_texture *tex, char **line_arg)
{
	DIR				*dir;

	if (ft_atoui_protected(line_arg[1], &tex->frame_ms)
		|| ft_atoui_protected(line_arg[2], &tex->frame_pause_ms))
		return (to_error_msg(MSG_WRONG_TIME), FAIL);
	if (in_2_tools_utiles_xpm_files_in_folder(line_arg[0], &tex->frame_number)
		== FAIL)
		return (FAIL);
	tex->frame_array = ft_calloc(tex->frame_number,
			sizeof(t_static_texture));
	if (!tex->frame_array)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	dir = opendir(line_arg[0]);
	if (!dir)
		return (to_error_msg(MSG_OPENDIR_FAIL), FAIL);
	if (_in_2_get_textures_from_directory(mlx, dir, line_arg[0], tex) == FAIL)
		return (closedir(dir), FAIL);
	closedir(dir);
	tex->frame_cycle_short = tex->frame_number * tex->frame_ms;
	tex->frame_cycle_long = tex->frame_cycle_short + tex->frame_pause_ms;
	in_2_utiles_sort_anim_text_array(tex->frame_array, tex->frame_number);
	return (SUCCESS);
}

/**
 * @brief initializes all the static textures of an animated texture based on
 *		the .xpm files contained in the given folder
 * 
 * @param mlx 
 * @param dir 
 * @param dir_name 
 * @param tex 
 * @return t_bool	SUCCESS if all the .xpm have been loaded successfully as
 *						static textures
 *					FAIL in case of allocation faillure or texture
 *						initialisation error
 *						-> error msg displayed, arguments untouched
 */
static t_bool	_in_2_get_textures_from_directory(void *mlx, DIR *dir,
	char *dir_name, t_animated_texture *texture)
{
	struct dirent	*elem;
	unsigned int	i;
	char			*path;

	i = 0;
	if (ft_strlen(dir_name) > 1 && dir_name[ft_strlen(dir_name) - 1] == '/')
		dir_name[ft_strlen(dir_name) - 1] = 0;
	elem = readdir(dir);
	while (elem && i < texture->frame_number)
	{
		if (in_2_utiles_is_xpm_file(elem))
		{
			path = to_file_build_path(dir_name, elem->d_name, NULL, NULL);
			if (!path)
				return (to_error_msg(MSG_BAD_ALLOC), FAIL);
			if (in_2_static_texture_init_one (mlx, &texture->frame_array[i],
					path) == FAIL)
				return (free(path), FAIL);
			++i;
		}
		elem = readdir(dir);
	}
	return (SUCCESS);
}

#endif

/*

//tests

static void	_in_2_show_static_text(t_static_texture *tex)
{
	if (tex)
		printf("- {%s} :\n  width = %d\n  height: %d\n  data.img = %p\n",
		tex->path, tex->img_width, tex->img_height, tex->data.img);
	else
	 printf("- (nill)\n");
}

static void	_in_2_show_animated_text(t_animated_texture *tex)
{
	unsigned int	i;
	printf("Texture: frame_number: %u\n frame_ms: %u\n frame_cycle_short: %u\n\
 frame_cycle_long: %u\n frame_array:\n", tex->frame_number, tex->frame_ms,
 	tex->frame_cycle_short, tex->frame_cycle_long);
	if (tex->frame_array)
	{
		i = 0;
		while (i < tex->frame_number)
			_in_2_show_static_text(&tex->frame_array[i++]);
	}
	else
		printf("(nill)\n");
}
*/

/*
//tests d'une unique texture animee (in_2_anim_textu_init)
int	main(int ac, char **av)
{
	char			**arg;
	t_general		gen;
	unsigned int	i;

	if (ac != 3 && ac != 5)
		return (printf("wrong format : expect {./a.out SO texture_path} \
or {./a.out SO text_repo_containing_img frame_ms frame_pause_ms}\n"), 0);

	gen = (t_general){0};
	in_0_init_display(&gen);
	printf("init ok\n\n");
	
	arg = av + 1;
	if (in_2_anim_textu_init(gen.disp.mlx, &gen.textures.wall_e, arg)
		== SUCCESS)
	{
		printf("Texture ok:\n");
		_in_2_show_animated_text(gen.textures.wall_e);
		i = 0;
		while (i < gen.textures.wall_e->frame_number)
		{
			mlx_put_image_to_window(gen.disp.mlx, gen.disp.win,
				gen.textures.wall_e->frame_array[i].data.img, 0, 0);
			sleep(2);
			++i;
		}
		printf("No more texture\n");
		mlx_put_image_to_window(gen.disp.mlx, gen.disp.win,
			gen.textures.wall_e->frame_array[1].data.img, 0, 0);
		mlx_loop(gen.disp.mlx);
	}
	else
		printf("Texture faillure\n");
	end_destroy_general(&gen);
	return (0);
}
*/
