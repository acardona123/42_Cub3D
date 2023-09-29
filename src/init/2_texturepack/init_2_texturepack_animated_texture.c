/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_animated_texture.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 01:53:53 by acardona          #+#    #+#             */
/*   Updated: 2023/09/29 19:42:40 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static t_bool	_in_2_anim_textu_init(void *mlx, t_animated_texture **texture,
					char **line_arg);
static t_bool	_in_2_anim_textu_init_file(void *mlx,
					t_animated_texture *texture, char **line_arg);
static t_bool	_in_2_anim_textu_init_folder(void *mlx,
					t_animated_texture *texture, char **line_arg);

t_bool	in_2_init_animated_texture(void *mlx, t_texture_pack *text_pack,
	char **line_arg, bool *already_done)
{
	if (!ft_strcmp(*line_arg, "NO"))
		return (_in_2_anim_textu_init(mlx, &text_pack->wall_n, line_arg));
	else if (!ft_strcmp(*line_arg, "SO"))
		return (_in_2_anim_textu_init(mlx, &text_pack->wall_s, line_arg));
	else if (!ft_strcmp(*line_arg, "WE"))
		return (_in_2_anim_textu_init(mlx, &text_pack->wall_w, line_arg));
	else if (!ft_strcmp(*line_arg, "EA"))
		return (_in_2_anim_textu_init(mlx, &text_pack->wall_e, line_arg));
	else if (!ft_strcmp(*line_arg, "DF"))
		return (_in_2_anim_textu_init(mlx, &text_pack->door_front, line_arg));
	else if (!ft_strcmp(*line_arg, "DL"))
		return (_in_2_anim_textu_init(mlx, &text_pack->door_side_l, line_arg));
	else if (!ft_strcmp(*line_arg, "DR"))
		return (_in_2_anim_textu_init(mlx, &text_pack->door_side_r, line_arg));
	else if (!ft_strcmp(*line_arg, "F"))
		return (in_2_set_color(&text_pack->color_f, line_arg,
				&already_done[IDX_FLOOR]));
	else if (!ft_strcmp(*line_arg, "C"))
		return (in_2_set_color(&text_pack->color_c, line_arg,
				&already_done[IDX_CEIL]));
	return (FAIL);
}

/**
 * @brief initializes the t_animated_texture structure of a texture based on a
 *			fragmented line of the input file. Two pssible syntaxes:
 *			unanimated texture (stored as animated with inly one static textu):
 *				elem_acronym text_img_path
 *			animated texture:
 *				elem_acronym text_repo_containing_img frame_ms frame_pause_ms
 * 
 * @param texture 
 * @param line_arg 
 * @return SUCCESS (textures successfully loaded)
 * @return FAIL (err msg displayed. no argument freed)
 */
static t_bool	_in_2_anim_textu_init(void *mlx, t_animated_texture **texture,
	char **line_arg)
{
	if (*texture)
		return (to_error_msg("Multiple definition of texture"), FAIL);
	*texture = ft_calloc(1, sizeof(t_animated_texture));
	if (!texture)
		return (to_error_msg("Mem alloc fail while textures init"), FAIL);
	if ((ft_tablen(line_arg) == 2
			&& _in_2_anim_textu_init_file(mlx, *texture, line_arg) == SUCCESS)
		|| (ft_tablen(line_arg) == 4 \
		&& _in_2_anim_textu_init_folder(mlx, *texture, line_arg) == SUCCESS))
		return (SUCCESS);
	return (FAIL);
}

/**
 * @brief generate the t_animated_texture in the case of only one path is given
 *		(without parametres for frame rates or so) => this path must be directly
 *		the xpm file path
 * 
 * @param mlx ptr to the mlx
 * @param texture struct to fill
 * @param line_arg splited line of the input file to import
 * @return SUCCESS: texture successfully imported, no arg freed
 * @return FAIL: err msg displayed, no arg freed
 */
static t_bool	_in_2_anim_textu_init_file(void *mlx,
	t_animated_texture *texture, char **line_arg)
{
	texture->frame_array = ft_calloc (1, sizeof(t_static_texture));
	if (!texture->frame_array)
		return (to_error_msg("Mem alloc fail while textures init"), FAIL);
	texture->frame_number = 1;
	texture->frame_ms = INT_MAX / 2;
	texture->frame_pause_ms = 0;
	texture->frame_cycle_short = INT_MAX / 2;
	texture->frame_cycle_long = INT_MAX / 2;
	texture->frame_array[0] = (t_static_texture){line_arg[1], 0, 0,
		(t_data){0}};
	if (in_2_static_texture_init_one(mlx, &texture->frame_array[0],
			line_arg[1]) == FAIL)
	{
		free(texture->frame_array);
		return (FAIL);
	}
	line_arg[1] = line_arg[ft_tablen(line_arg) - 1];
	line_arg[ft_tablen(line_arg) - 1] = NULL;
	return (SUCCESS);
}

#ifdef BONUS

/**
 * @brief fills t_animated_texture structure based on the line_arg elements:
 *	elem_acronym text_repo_containing_img frame_ms frame_pause_ms
 * @param mlx 
 * @param texture 
 * @param line_arg 
 * @return true SUCCESS: textures successfully imported, no arg freed
 * @return FAIL : err msg displayed, no arg freed
 */
static t_bool	_in_2_anim_textu_init_folder(void *mlx,
	t_animated_texture *tex, char **line_arg)
{
	DIR				*dir;
	struct dirent	*elem;
	unsigned int	i;
	char			*path;

	if (ft_atoui_protected(line_arg[2], &tex->frame_ms)
		|| ft_atoui_protected(line_arg[3], &tex->frame_pause_ms))
		return (to_error_msg("Wrong time argument"), FAIL);
	if (in_2_tools_count_xpm_files_in_folder(line_arg[1], &tex->frame_number) == FAIL)
		return (FAIL);
	tex->frame_array = ft_calloc(tex->frame_number,
			sizeof(t_static_texture));
	if (!tex->frame_array)
		return (to_error_msg("Mem alloc faillure in texture init"), FAIL);
	dir = opendir(line_arg[1]);
	if (!dir)
		return (to_error_msg("Wrong texture directory"), FAIL);
	i = 0;
	elem = readdir(dir);
	while (elem && i < tex->frame_number)
	{
		if (elem->d_type == DT_REG && ft_strlen(elem->d_name) >= 4
			&& !ft_strcmp(elem->d_name + ft_strlen(elem->d_name) - 4, ".xpm"))
		{
			path = ft_strjoin3(line_arg[1], "/", elem->d_name);
			if (!path)
				return (closedir(dir),
					to_error_msg("Mem alloc faillure in texture init"), FAIL);
			if (in_2_static_texture_init_one (mlx, &tex->frame_array[i],
					path) == FAIL)
				return (closedir(dir), free(path), FAIL);
			++i;
		}
		elem = readdir(dir);
	}
	tex->frame_cycle_short = tex->frame_number * tex->frame_ms;
	tex->frame_cycle_long = tex->frame_cycle_short + tex->frame_pause_ms;
	in_2_tools_sort_anim_text_table(tex->frame_array, tex->frame_number);
	return (closedir(dir), SUCCESS);
}
#endif

#ifndef BONUS
/**
 * @brief can't open a folder in the mandatory part
 * 
 * @param mlx ignored
 * @param texture ignored
 * @param line_arg ignored
 * @return FAIL ALWAYS
 */
static t_bool	_in_2_anim_textu_init_folder(void *mlx,
	t_animated_texture **texture, char **line_arg)
{
	(void)mlx;
	(void)texture;
	(void)line_arg;
	return (to_error_msg("Cannot open folder in the mandatry part"), FAIL);
}

#endif

/*
static void	_in_2_show_static_text(t_static_texture *tex)
{
	if (tex)
		printf("- {%s} :\n  width = %d\n  height: %d\n  data.img = %p\n", tex->path,
		tex->img_width, tex->img_height, tex->data.img);
	else
	 printf("- (nill)\n");
}

static void	_in_2_show_animated_text(t_animated_texture *tex)
{
	unsigned int	i;
	printf("Texture: frame_number: %u\n frame_ms: %u\n frame_cycle_short: %u\n frame_cycle_long: %u\n frame_array:\n", tex->frame_number, tex->frame_ms, tex->frame_cycle_short, tex->frame_cycle_long);
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
//tests d'une unique texture animee (_in_2_anim_textu_init)
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
	if (_in_2_anim_textu_init(gen.disp.mlx, &gen.textures.wall_e, arg) == SUCCESS)
	{
		printf("Texture ok:\n");
		_in_2_show_animated_text(gen.textures.wall_e);
		i = 0;
		while (i < gen.textures.wall_e->frame_number)
		{
			mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.textures.wall_e->frame_array[i].data.img, 0, 0);
			sleep(2);
			++i;
		}
		printf("No more texture\n");
		mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.textures.wall_e->frame_array[1].data.img, 0, 0);
		mlx_loop(gen.disp.mlx);
	}
	else
		printf("Texture faillure\n");
	end_destroy_general(&gen);
	return (0);
}
*/

